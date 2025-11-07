#include "Discount.h"
#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    Date val_date(2022, 11, 4);
    std::vector<Date> expiries = {
        Date(2022, 12, 4),
        Date(2023, 1, 4),
        Date(2023, 5, 4),
        Date(2023, 8, 4),
        Date(2024, 12, 4),
        Date(2027, 12, 4)
    };
    std::vector<double> rates = {0.04, 0.045, 0.0475, 0.045, 0.0375, 0.035};

    Discount usd_curve(val_date, expiries, rates);

    std::cout << "Valuation Date: " << usd_curve.valuation_date() << "\n";
    std::cout << "Date          T(yrs)     Discount\n";
    std::cout << "----------------------------------\n";


    for (auto& d : expiries) {
        double T = (d - val_date) / 365.0;
        double df = usd_curve.discount(d);
        std::cout << d << "  "
                << std::setw(8) << std::fixed << std::setprecision(3) << T
                << "  " << std::setw(10) << std::setprecision(6) << df
                << "\n";

    }

    return 0;
}
