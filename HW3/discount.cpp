#include <cmath>
#include <algorithm>
#include "discount.h"
using namespace std;

//
// compute the discount factor (price of a zero-coupon bond)
// given the interest rate r and the time to expiry T in years
// 
double discount(double T, double r) {
    return exp(-r*T);
}
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
double swap_rate(double T, double freq,  double r) {
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

