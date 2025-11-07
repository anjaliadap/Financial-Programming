#pragma once
#include <vector>
#include "Date.h"
#include "interpolate.h"

/**
 * @brief Represents a simple discount curve defined by zero rates.
 *
 * The discount factor for a given date is computed as:
 *    df(date) = exp(-r(T) * T)
 * where T is the year fraction between the valuation date and the input date.
 *
 * Preconditions:
 *  - expiries and rates have the same size and are sorted in increasing date order
 *  - rates correspond to continuously compounded zero rates
 */
class Discount {
public:
    /**
     * @brief Construct a Discount curve.
     * @param value_date Valuation date.
     * @param expiries   Vector of expiry dates (must be sorted ascending).
     * @param rates      Corresponding interest rates.
     */
    Discount(Date value_date,
             const std::vector<Date>& expiries,
             const std::vector<double>& rates);

    /**
     * @brief Returns the discount factor for a given date.
     * @param date Input date.
     * @return exp(-r(T) * T) where r(T) is interpolated rate and T = (date - valuation_date) / 365.
     */
    double discount(Date date) const;

    /**
     * @brief Returns the valuation date of this discount curve.
     */
    Date valuation_date() const;

private:
    Date m_valuation_date;
    std::vector<double> m_Ts;    // years to expiry (T = (expiry - valuation_date)/365)
    std::vector<double> m_rates; // corresponding interest rates
};

Discount parse_discount(std::istream &input);
