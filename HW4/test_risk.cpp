#include <iostream>
#include "black_scholes.h"
using namespace std;

int main() {
    
    int  units[]={1000,1000,-1000,-1000};
    bool is_call[]={true,false,true,false};
    double K[]={110,90,120,80};
    double T[]={1.0,1.0,1.5,1.5};
    int noptions = sizeof(units) / sizeof(units[0]);

    double S=100.0;
    double tenors;
    double Ts[]={1.0,2.0,5.0};  
    double rs[]={0.055,0.0525,0.05};
    double ds[]={0.0125,0.015,0.0175};
    double sigmas[]={0.25,0.26,0.265};
    tenors = sizeof(Ts) / sizeof(Ts[0]);

    double* value = new double[noptions];
    double* delta = new double[noptions];
    double* gamma = new double[noptions];
    double* vega  = new double[noptions];
    double* DV01  = new double[noptions];

    bs_risk_portfolio(noptions, units, is_call, K, T, S,
                      tenors, Ts, rs, ds, sigmas,
                      value, delta, gamma, vega, DV01);

    cout << "notional, is_call, K, T, value, delta, gamma, vega, DV01\n";

    for (int i = 0; i < noptions; ++i) {
        cout << units[i] << ", "
            << (is_call[i] ? 1 : 0) << ", "
            << K[i] << ", "
            << T[i] << ", "
            << value[i] << ", "
            << delta[i] << ", "
            << gamma[i] << ", "
            << vega[i]  << ", "
            << DV01[i]  << '\n'; 
    }

    double total_delta=0.0, total_gamma=0.0, total_vega=0.0, total_DV01=0.0;
    double total_value = total_risk(noptions, value, delta, gamma, vega, DV01,
                                  total_delta, total_gamma, total_vega, total_DV01);

    cout << "\nTotal Risk\n";
    cout << "value, delta, gamma, vega, DV01\n";
    cout << total_value << ", " << total_delta << ", " << total_gamma << ", "
         << total_vega  << ", " << total_DV01 << '\n';

    delete[] value; delete[] delta; delete[] gamma; delete[] vega; delete[] DV01;

    return 0;
}   