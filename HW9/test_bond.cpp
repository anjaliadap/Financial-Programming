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

    // Output only the price for each bond
    for (const auto &b : bonds) {
        double price = 0.0;

        if (b.currency == "USD")
            price = b.price(usd_curve);
        else if (b.currency == "EUR")
            price = b.price(eur_curve);
        else
            continue; // skip unknown currency

        // Print price in scientific notation
        std::cout << std::scientific << std::setprecision(5) << price << "\n";
    }

    return 0;
}
