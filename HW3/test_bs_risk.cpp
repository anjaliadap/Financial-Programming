#include <iostream>
#include <iomanip>
#include "black_scholes.h"
#include "discount.h"
using namespace std;

int main() {
    // Market inputs
    const double S     = 110.0;
    const double r     = 0.054;
    const double d     = 0.03;
    const double sigma = 0.25;
    const double T     = 1.0;   // one year
    const bool isCall  = true;

    // Output CSV header
    std::cout << "K, Price, Delta, Gamma, Vega, DV01\n";

    // Loop over strikes K = 50, 60, ..., 200
    for (double K = 50.0; K <= 200.0; K += 10.0) {
        double delta, gamma, vega, rho;

        // call bs_risk -> returns price, sets Greeks by reference
        double price = bs_risk(isCall, K, T, S, r, d, sigma,
                               delta, gamma, vega, rho);

        // Convert rho to DV01 (price change for 1bp = 0.0001)
        double dv01 = -rho * 1e-4;

        // Print row as CSV
        std::cout << fixed
                  << setprecision(2) << K << ", "
                  << setprecision(2) << price << ", "
                  << delta << ", "
                  << gamma << ", "
                  << vega  << ", "
                  << dv01  << "\n";
    }

    return 0;
}