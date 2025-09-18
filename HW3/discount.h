#pragma once

#include <cmath>
using namespace std;
//
// compute the discount factor (price of a zero-coupon bond)
// given the interest rate r and the time to expiry T in years
// 
double discount(double T, double r);
//
// compute the present value of a bond cash flows
// given level of interest rate r
// The bond is described by
//      T:       time to maturity of bond
//      coupon: annualized interest payment
//      freq:   coupon frequency, number of coupon payments per year
//

double bond_pv(double T,double coupon, double freq, double r) {
    double price=0.0;
    double dT=1.0/freq;
    double t=0.0;
    while (t<T) {
        double dt=min(dT,T-t);
        double df=discount(t+dt,r);
        price+=coupon*df*dt;
        t+=dT;
    }
    price+=discount(T,r); // return of principal
    return price;
}

// 
// compute the swap par rate given the level of interest rates r
//  the time to maturity T, and the frequency of payments freq
//
double swap_rate(double T, double freq, double r) {
    double DV01 = 0.0;
    double dT = 1.0/freq;
    double t = 0.0;

    while (t<T) {
        double dt = min(dT,T-t);
        double df = discount(t+dt,r);
        DV01 += df * dt;
        t += dT;
    }

    double rate = (1.0-discount(T,r)) / DV01;
 
    return rate;
}

// 
// compute the swap present value givent the inputs:
//         is_receiver: true if the swap is a receiver fix swap, false if it is a payer swap
//         R:           the swap  rate    
//         T:           the time to maturity of the swap
//         freq:        the frequency of payments of the swap
//         r:           the current level of interest rates (continuously compounded
//                          zero coupon rate)
//
double swap_pv(bool is_receiver, double R, double T, double freq,  double r) {

    double pv = 0.0;
    double dT = 1.0 / freq; 
    double sign = (is_receiver ? +1 : -1);
    double ti;

    // Number of whole intervals before T 
        // T is total time to maturity
    int N = (int)floor(T * freq); // getting the total number of time periods 

     // 1. Regular fixed coupons at t = dT, 2dT, ..., (N-1)dT
    for(int i = 1; i <= N-1; ++i) {
        ti = i * dT; // increments of the time period to discount by {e.g. 0.5, 1.0, 1.5, 2.0, ...}

        pv += sign * R * dT * discount(ti, r); // conditional statement 
    }

    // 2. Payment of last remaining period if T is decimal 
    double t_last = (N >= 1) ? (N - 1) * dT : 0.0;
    double dt     = T - t_last;  
  
    pv += (sign * R * dt * discount(T, r));

    // 3. Floating leg 
    pv += (sign * (discount(T, r) - 1.0));

    return pv;
}