#include <iostream>
#include <iomanip>
#include <cmath>
#include "discount.h"

using namespace std;

int main() {
    const double r = 0.06;   // continuously compounded flat rate
    const double freq = 2.0; // semi-annual payments
    const double dt = 0.25;  // maturity step in years (quarterly)
    const double T_max = 30.0;
    const double tol = 1e-12;

    // CSV header
    cout << "T, R, pv\n";

    // Loop T = 0.25, 0.50, ..., 30.00
    for (double T = dt; T <= T_max; T += dt) {

        double R  = swap_rate(T, freq, r);
        double pv = swap_pv(true, R, T, freq, r);

        // For neat CSV output
        cout << fixed << std::setprecision(2) << T << ", " << R << ", " << std::setprecision(2) << pv << '\n';
    
    }
    
    return 0;

}

   
