#include "discount.h"
#include <cmath>
using  namespace std;
double discount(double t, int tenors, 
                const double *Ts, const double *rs) {
    int index=0;
    while (index<tenors && Ts[index]<t) {
        index++;
    }
    double r;
    if (index==0) {  // t<Ts[0] flat extrapolation
        r=rs[0];
    } else if (index==tenors) { // t>Ts[tenors-1] 
        r=rs[tenors-1];
    } else {;        // Ts[index-1]<t<Ts[index] 
        double r1=rs[index];
        double t1=Ts[index];
        int index0=index-1;
        double t0=Ts[index0];
        double r0=rs[index-1];
    
        double dt=t-t0;
        double dr=r1-r0;
        r=r0+dr*dt/(t1-t0);//linear interpolation
    }
    return exp(-r*t);
}

double bond_pv(double T,double coupon, double freq, 
        int tenors, const double *Ts, const double *rs) {
    double price=0.0;
    double dT=1.0/freq;
    double t=0.0;
    while (t<T) {
        double dt=min(dT,T-t);
        double df=discount(t+dt,tenors,Ts,rs);
        price+=coupon*df*dt;
        t+=dT;
    }
    price+=discount(T,tenors,Ts,rs); // return of principal
    return price;
}


double swap_rate(double T, double freq, 
            int tenors, const double *Ts, const double *rs) {
    double DV01=0.0;
    double dT=1.0/freq;
    double t=0.0;
    while (t<T) {
        double dt=min(dT,T-t);
        double df=discount(t+dt,tenors,Ts,rs);
        DV01+=df*dt;
        t+=dT;
    }
    double rate=(1.0-discount(T,tenors,Ts,rs))/DV01;
    return rate;
}
