#include <cmath>
#include "discount.h"
#include "forward.h"
#include "black_scholes.h"

static double ndtr(double z) {
    return 0.5*(1+std::erf(z/std::sqrt(2)));
};

double bs_price_fwd(bool is_call, double K, double T,
                    double F, double sigma) 
{  
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

double bs_price(bool isCall, double K, double T, 
                double df, double F, double sigma) {
    double fwd_price=bs_price_fwd(isCall, K, T, F, sigma);
    return df*fwd_price;
}

double bs_price(bool isCall, double K, double T, 
               double S, double r, 
               double d, double sigma) {
    double df=discount(T,r);
    double F=forward(T,S,r,d);
    return bs_price(isCall, K, T, df, F, sigma);
}

double bs_risk(bool isCall, double K, double T, 
               double S, double r, 
               double d, double sigma,
               double &delta, double &gamma, double &vega, double &rho) {

    // Discount factor and forward price
    const double df    = discount(T, r);        // e^{-rT}
    const double F     = forward(T, S, r, d);   // S e^{(r-d)T}
    const double sqrtT = std::sqrt(T);

    // d1, d2
    const double x   = std::log(F / K);
    const double ds  = sigma * sqrtT;
    const double d2  = (x - 0.5 * ds * ds) / ds;
    const double d1  = d2 + ds;

    // Option price
    const double price = bs_price(isCall, K, T, df, F, sigma);

    // Common factors
    const double qdf = discount(T, d);                      // dividend discount
    const double INV_SQRT_2PI = 0.398942280401432677939946;   // 1/sqrt(2π)
    const double phi_d1 = INV_SQRT_2PI * std::exp(-0.5 * d1 * d1);

    if (isCall) {
        delta = qdf * ndtr(d1);
        gamma = qdf * phi_d1 / (S * ds);
        vega  = qdf * S * phi_d1 * sqrtT;
        rho   = K * df * T * ndtr(d2);
    } else {
        delta = qdf * (ndtr(d1) - 1.0);
        gamma = qdf * phi_d1 / (S * ds);
        vega  = qdf * S * phi_d1 * sqrtT;
        rho   = -K * df * T * ndtr(-d2);
    }

    return price;
}