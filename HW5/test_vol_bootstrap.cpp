#include "discount.h"
#include "forward.h"
#include "volatility.h"
#include "black_scholes.h"

#include <iostream>
using namespace std;

int main() {
    const int tenors=5;
    double Ts[tenors]={0.5,1,2,3,5};
    bool is_call[tenors]={true,true,true,true};
    double Ks[tenors]={100,100,100,100,100};
    double S=100;
    double freq=1;
    double Rs[tenors]={0.05,0.055,0.0525,0.05,0.04}; // swap rates
    double ds[tenors]={0.01,0.0125,0.01275,0.02,0.0225};

    // Array of Option price curves
    double prices[][tenors]={       
        {7.95278,12.1187,17.8417,20.846,17.481},
        {6.5782,9.76115,14.2884,16.2222,101.2667},
        {6.5782,9.76115,14.2884,16.2222,11.2667},
        {7.95278,9.85515,11.0634,9.29034,1.94972}
    };

    // Problem 2.3: bootstrap swap curve
    double rs[tenors]={0.0,0.0,0.0,0.0,0.0};
    {
        const int max_iter = 200;
        const double tol   = 1e-12;
        int status = swap_bootstrap(tenors, Ts, Rs, freq, rs, max_iter, tol);
        if (status != 0) {
            // If zero-curve bootstrap fails, nothing else can proceed
            cout << "Could not bootstrap volatility curve 0" << endl;
            return 0;
        }
    }

    // Problem 2.4: bootstrap volatility curves
    const int num_curves = (int)(sizeof(prices)/sizeof(prices[0]));

    for (int i = 0; i < num_curves; ++i) {
        double sigmas[tenors] = {0.0,0.0,0.0,0.0,0.0};
        const int max_iter = 200;
        const double tol   = 1e-10;

        int status = volatility_bootstrap(
            tenors,
            is_call,
            Ks,
            Ts,
            S,
            rs,    // zero curve from swap bootstrap
            ds,    // dividend curve
            prices[i], // this curve's option prices
            sigmas,
            max_iter, tol
        );

        if (status > 0) {
            // solver could not find implied vol at tenor index (status-1)
            cout << "Could not bootstrap volatility curve " << i << endl;
            continue;
        } else if (status < 0) {
            // no-arbitrage violation: sigma^2(T) * T not nondecreasing
            cout << "Volatility Curve " << i << " is arbitrageable" << endl;
            continue;
        }

        for (int j = 0; j < tenors; ++j) {
            if (j) cout << ",";
            cout << sigmas[j];
        }
        cout << endl;
    }
    
    return 0;   
}