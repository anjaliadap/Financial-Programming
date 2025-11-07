#include "Discount.h"
#include <iostream>
#include <fstream>
#include <iomanip>

int main() {
    std::ifstream file("discount_usd.txt");
    if (!file.is_open()) {
        std::cerr << "Error: could not open discount_usd.txt\n";
        return 1;
    }

    Discount usd_curve = parse_discount(file);
    file.close();

    Date val_date = usd_curve.valuation_date();
    std::cout << "valuation_date," << val_date << "\n";
    std::cout << "date,rate\n";

    for (int i = 0; i <= 40; ++i) { // every 90 days for 10 years
        Date d = val_date + 90.0 * i;
        double T = (d - val_date) / 365.0;
        double df = usd_curve.discount(d);
        std::cout << d << "," << std::fixed << std::setprecision(6) << df << "\n";
    }

    return 0;
}
