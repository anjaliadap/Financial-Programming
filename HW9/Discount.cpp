#include "Discount.h"
#include <cmath>
#include <stdexcept>
#include <sstream>

Discount::Discount(Date value_date,
                   const std::vector<Date>& expiries,
                   const std::vector<double>& rates)
    : m_valuation_date(value_date),
      m_rates(rates)
{
    if (expiries.size() != rates.size())
        throw std::invalid_argument("Expiries and rates must have the same size");

    m_Ts.resize(expiries.size());
    for (size_t i = 0; i < expiries.size(); ++i) {
        m_Ts[i] = (expiries[i] - value_date) / 365.0;
    }
}

double Discount::discount(Date date) const {
    double T = (date - m_valuation_date) / 365.0;
    double r = interpolate(T, m_Ts, m_rates);
    return std::exp(-r * T);
}

Date Discount::valuation_date() const {
    return m_valuation_date;
}

Discount parse_discount(std::istream &input) {
    std::string line;

    // Step 1: Read valuation date (skip blank lines)
    Date valuation_date;
    while (std::getline(input, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        ss >> valuation_date;
        if (!ss.fail()) break;
    }

    if (!input)
        throw std::runtime_error("Failed to read valuation date");

    // Step 2: Read expiry and rate pairs
    std::vector<Date> expiries;
    std::vector<double> rates;

    while (std::getline(input, line)) {
        if (line.empty()) continue; // skip blank lines
        std::istringstream ss(line);
        Date expiry;
        double rate;
        ss >> expiry >> rate;
        if (ss.fail()) continue; // ignore malformed lines
        expiries.push_back(expiry);
        rates.push_back(rate);
    }

    if (expiries.empty())
        throw std::runtime_error("No expiry data found in discount file");

    // Step 3: Construct and return Discount object
    return Discount(valuation_date, expiries, rates);
}