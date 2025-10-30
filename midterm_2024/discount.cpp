#include <cmath>
#include "discount.h"
#include "solve.h"

using  namespace std;

double discount(double t
                , int tenors
                , const double *Ts
                , const double *rs) {

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

double swap_pv(bool is_receiver,double R, double T, double freq, 
               int tenors, const double *Ts, const double *rs) {
    double price=0.0;
    double dT=1.0/freq;
    double t=0.0;
    while (t<T) {
        double dt=min(dT,T-t);
        double df=discount(t+dt,tenors,Ts,rs);
        price+=R*df*dt;
        t+=dT;
    }
    price+=discount(T,tenors,Ts,rs)-1; // return of principal
    double notional=-1;
    if (is_receiver) notional=1;
    return notional*price;
}

double swap_function(double r, int size, double *params) {
    int tenors=((int)size-3)/2;
    int T_i=(int)params[0];
    double R=params[1];
    double freq=params[2];
    double *Ts=params+3;
    double *rs=Ts+tenors;
    rs[T_i]=r; // gradually fill the array of zero coupon rates
    return swap_rate(Ts[T_i],freq,tenors,Ts,rs)-R;
}

int  swap_bootstrap(int tenors, const double *Ts, const double *Rs, 
       double freq, double * rs, int max_iter, double tol) {
    // set parameter array for the swap_function
    int size=3+2*tenors;
    double * params=new double[size];
    params[0]=0; // to be filled later
    params[1]=0; // to be filled later
    params[2]=freq;
    for (int i=0;i<tenors;i++) {
        params[3+i]=Ts[i];
        params[3+tenors+i]=0; // to be filled later
    }
    // solve for the swap rates
    double x0=-0.1; // minimum -10% annualized rate
    double x1=0.5; // maximum 50% annualized rate
    for (int index=0;index<tenors;index++) {
        params[0]=index;
        params[1]=Rs[index]; // target
        double x=Rs[index]; // inital guess of the swap rate   
        double r;
        int status=solve_bisection(x,x0,x1,swap_function,
                                   size,params,max_iter,tol,r);
        if (status!=0) {
            delete[] params;
            return status;
        }
        rs[index]=r; //store  the zero coupon rate
    }
    delete[] params;
    return 0;
}

double bond_function(double r, int size, double *params)
{
    int tenors=((int)size-4)/2;
    int T_i=(int)params[0];
    double coupon=params[1];
    double price=params[2];
    double freq=params[3];
    double *Ts=params+4;
    double *rs=Ts+tenors;
    rs[T_i]=r; // gradually fill r array
    return bond_pv(Ts[T_i],coupon,freq,tenors,Ts,rs)-price;
}

int bond_bootstrap(int tenors, double *Ts, double *coupons, 
                   double *prices,double freq, double * rs,
                   int max_iter, double tol) {
  // set parameter array for the swap_function
    int size=4+2*tenors;
    double * params=new double[size];
    params[0]=0; // to be filled later
    params[1]=0; // to be filled later
    params[2]=0; // to be filled later
    params[3]=freq; 
    for (int i=0;i<tenors;i++) {
        params[4+i]=Ts[i];
        params[4+tenors+i]=0; // to be filled later
    }
    // solve for the swap rates
    double x0=-0.1; // minimum -10% annualized rate
    double x1=0.5; // maximum 10% annualized rate
    for (int index=0;index<tenors;index++) {
        params[0]=index;
        params[1]=coupons[index]; 
        params[2]=prices[index];
        double x=coupons[index]; // inital guess of the swap rate   
        double r;
        int status=solve_bisection(x,x0,x1,bond_function,
                                   size,params,max_iter,tol,r);
        if (status!=0) {
            delete[] params;
            return status;
        }
        rs[index]=r; //store  the zero coupon rate
    }
    delete[] params;
    return 0;
}