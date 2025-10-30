#include <cmath>
#include <iostream>
#include "discount.h"
using namespace std;

int main() {

    double Ts[] = {1.0, 2.0, 5.0, 10, 30};
    double rs[] = {0.055, 0.0525, 0.05, 0.0475, 0.0450}; // zero-rates for each maturity 
    
    int tenors = sizeof(Ts); // total number of years and their maturities
    
    double freq = 1; // numebr of coupon payments in a year 

    cout << "T, par_rate, swap_pv, bond_pv" << endl;
  
    for (double T = 0.25; T <= 10; T += 0.25) {
    
        double R        = swap_rate(T, freq, tenors, Ts, rs);
        double pv_swap  = swap_pv(true, R, T, freq, tenors, Ts, rs); 
        double pv_bond  = bond_pv(T, R, freq, tenors, Ts, rs);       
        
        cout << T << ", " << R << ", "<< pv_swap << ", " << pv_bond << endl;
    }

    return 0; 
}