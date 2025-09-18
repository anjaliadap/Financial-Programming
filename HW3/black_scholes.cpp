#include <cmath>
#include "discount.h"
#include "forward.h"
#include "black_scholes.h"

static double ndtr(double z) {
    return 0.5*(1+std::erf(z/std::sqrt(2)));
};

// standard normal PDF φ(x)
static double nphi(double x) {
    static const double INV_SQRT_2PI = 0.3989422804014327; // 1 / sqrt(2π)
    return INV_SQRT_2PI * std::exp(-0.5 * x * x);
}

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