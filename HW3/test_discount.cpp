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

    cout << "T, R, pv\n";

    // Loop T = 0.25, 0.50, ..., 30.00
    for (double T = dt; T <= T_max; T += dt) {

        double R  = swap_rate(T, freq, r);
        double pv = swap_pv(true, R, T, freq, r);
        
        pv = abs(pv);

        cout << fixed << setprecision(2) << T << ", " << R << ", " << setprecision(2) << pv << '\n';
    
    }
    
    return 0;

}

   
