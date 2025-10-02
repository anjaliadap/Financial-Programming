#include "discount.h"
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

int main() {

    int tenors=5;
    double Ts[tenors]={1.0,2.0,5.0,10,30};
    double coupons[tenors]={0.025,0.0325,0.045,0.045,0.0475};
    double prices[tenors]={ 1.02, 1.05,1.01,0.99,0.98};
    double freq=1.0;
    
    // Problem 1.3 Bootstrap discount curve
    //             given inputs above

    double rs[tenors] = {0.0, 0.0, 0.0, 0.0, 0.0};
    const int    max_iter = 200;
    const double tol      = 1e-10;

    int status = bond_bootstrap(tenors, Ts, coupons, prices, freq, rs, max_iter, tol);
    if (status != 0) {
        cerr << "bond_bootstrap failed with status = " << status << "\n";
        return 1;
    }

    cout<<"T, zero_rate, bond_price"<<endl;
    cout << fixed << setprecision(5);
    for (int i = 0; i < tenors; ++i) {
        double T = Ts[i];
        double zr = rs[i];  // bootstrapped zero at T

        cout << setw(0) << T
             << setw(10) << zr
             << setw(10) << prices[i]
             << "\n";
    }

    return 0;
}