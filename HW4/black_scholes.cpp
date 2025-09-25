#include "discount.h"
#include "forward.h"
#include "volatility.h"
#include "black_scholes.h"

#include <cmath>


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

double bs_risk(bool is_call, double K, double T, double S, int tenors, const double *Ts,const double *rs, 
    const double *ds, const double *sigmas, double &delta, double &gamma, double &vega, double &DV01) {

    double df    = discount(T, tenors, Ts, rs);
    double F     = forward (T, S, tenors, Ts, rs, ds);
    double sigma = volatility(T, tenors, Ts, sigmas);
    double V0    = bs_price(is_call, K, T, df, F, sigma);

    double dS  = 0.01 * S;                  
    double Sup = S + dS;
    double Sdn = S - dS; 

    double Fp = forward(T, Sup, tenors, Ts, rs, ds); // F+
    double Fm = forward(T, Sdn, tenors, Ts, rs, ds); // F-

    double Vp = bs_price(is_call, K, T, df, Fp, sigma);
    double Vm = bs_price(is_call, K, T, df, Fm, sigma);

    delta = (Vp - Vm) / (2.0 * dS);
    gamma = (Vp - 2.0 * V0 + Vm) / (dS * dS);

    double dsigma = 0.01;
    double Vsig_up = bs_price(is_call, K, T, df, F, sigma + dsigma);
    vega = Vsig_up - V0;

    double dr  = 0.0001;
    double dfr = df * std::exp(-dr * T);
    double Fr  = F  * std::exp( dr * T);
    double V_up_r = bs_price(is_call, K, T, dfr, Fr, sigma);
    DV01 = V_up_r - V0;  

    return V0;

}

void bs_risk_portfolio(
    int noptions,
    const int *units,
    const bool *is_call,
    const double *K,
    const double *T,
    double S,
    int tenors, const double *Ts,const double *rs,
    const double *ds, const double *sigmas,
    double *value,
    double *delta, double *gamma, double *vega, double *DV01)
{

    for (int i = 0; i < noptions; ++i) {
        double d=0.0, g=0.0, v=0.0, dv=0.0;
        double v0 = bs_risk(is_call[i], K[i], T[i], S, tenors, Ts, rs, ds, sigmas, d, g, v, dv);

        value[i] = v0 * units[i];
        delta[i] = d  * units[i];
        gamma[i] = g  * units[i];
        vega[i]  = v  * units[i];
        DV01[i]  = dv * units[i];
    }
}

double total_risk(
    int noptions,
    const double *values,
    const double *deltas,
    const double *gammas,
    const double *vegas,
    const double *DV01s,
    double &delta, double &gamma, double &vega, double &DV01)
{
    double total_value = 0.0, total_delta = 0.0, total_gamma = 0.0, total_vega = 0.0, total_dv01 = 0.0;

    for (int i = 0; i < noptions; ++i) {
        total_value += values[i];
        total_delta += deltas[i];
        total_gamma += gammas[i];
        total_vega  += vegas[i];
        total_dv01  += DV01s[i];
    }

    delta = total_delta;
    gamma = total_gamma;
    vega  = total_vega;
    DV01  = total_dv01;

    return total_value;
}