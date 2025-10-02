#include "discount.h"
#include "forward.h"
#include "volatility.h"
#include "black_scholes.h"
#include "solve.h"

#include <cmath>
#include <iostream>


double ndtr(double z) {
    return 0.5*(1+std::erf(z/std::sqrt(2)));
};

//
// Black's pricing formula:
// European option  forward (undiscounted) price as a function of
//    the asset's forward
// <isCall> true for calls , false for puts
// <K> option strike  
// <T> option expiry in years
// <F> forward of the options underlying asset
// <sigma> underlying's  volatility
// returns forwarded (undiscounted)  option's price
//


double bs_price_fwd(bool is_call, double K, double T,
                    double F, double sigma) {  
    double ds=std::max(0.000001,sigma*std::sqrt(T));
    double dsig=0.5*ds*ds;
    double d2=(log(F/K)-dsig)/ds;
    double d1=d2+ds;
    double opt;
    if (is_call)
        opt= F*ndtr(d1) - K*ndtr(d2);
    else
        opt= K*ndtr(-d2) - F*ndtr(-d1);
    return opt;
}

double bs_price(bool is_call,  double K, double T, 
                     double df, double F, double sigma) {
    return df*bs_price_fwd(is_call,K,T,F,sigma);
}

double bs_price(bool is_call, double K, double T, 
            double S,
            int tenors, const double *Ts, const double *rs, 
            const double *ds, const double *sigmas) {
    double df=discount(T,tenors,Ts, rs);
    double F=forward(T, S, tenors, Ts, rs, ds);
    double sigma=volatility(T, tenors, Ts, sigmas);
    return bs_price(is_call,K,T,df,F,sigma);
}
double price_function(double sigma, int size, double *params) {
    bool is_call=(params[0]!=0.0);
    double K=params[1];
    double T=params[2];
    double F=params[3];
    double price_fwd=params[4];
    return bs_price_fwd(is_call,K,T,F,sigma)-price_fwd;
}

int bs_implied_vol(bool is_call,double K, double T, double F, 
                   double price_fwd, double & sigma,
                   int max_iter, double tol) {
    double params[5];
    params[0]=is_call;
    params[1]=K;
    params[2]=T;
    params[3]=F;
    params[4]=price_fwd;
    double x=0.2; // initial guess of 20% annualized volatility
    double x0=0.0001; // minimum 0.01% annualized volatility
    double x1=1.0; // maximum 100% annualized volatility
    return solve_bisection(x,x0,x1,price_function,
                           5,params,max_iter,tol,sigma);
}

