#include "Bond.h"
#include "Discount.h"
#include <fstream>
#include <iostream>
#include <iomanip>

int main() {
    // Parse USD discount curve
    std::ifstream usd_file("discount_usd.txt");
    Discount usd_curve = parse_discount(usd_file);

    // Parse EUR discount curve
    std::ifstream eur_file("discount_eur.txt");
    Discount eur_curve = parse_discount(eur_file);

    // Parse bonds
    std::ifstream bond_file("bonds.txt");
    auto bonds = parse_bonds(bond_file);

    std::cout << std::setw(8) << "Currency"
              << std::setw(12) << "Notional"
              << std::setw(12) << "Coupon"
              << std::setw(12) << "Maturity"
              << std::setw(14) << "Price\n";
    std::cout << "------------------------------------------------------------\n";

    for (const auto &b : bonds) {
        double price = 0.0;
        if (b.currency == "USD")
            price = b.price(usd_curve);
        else if (b.currency == "EUR")
            price = b.price(eur_curve);
        else
            continue;

        std::cout << std::setw(8) << b.currency
                  << std::setw(12) << std::fixed << std::setprecision(0) << b.notional
                  << std::setw(12) << std::setprecision(3) << b.coupon
                  << std::setw(12) << b.maturity
                  << std::setw(14) << std::setprecision(2) << price
                  << "\n";
    }

    return 0;
}
