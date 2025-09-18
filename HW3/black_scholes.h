#pragma once
//
// Black's pricing formula:
// European option  forward (undiscounted) price as a function of
//    the asset's forward
// <isCall> true for calls , false for puts
// <K> option strike  
// <T> option expiry in years
// <F> forward of the options underlying asset
// <sigma> underlying's  volatility
// returns forward (undiscounted)  option's price
//
double bs_price_fwd(bool isCall, double K, double T, 
                    double F, double sigma);

//
// Black Scholes pricing formula:
// European option  forward (discounted) price as a function of
//    the asset's forward
// <isCall> true for calls , false for puts
// <K> option strike  
// <T> option expiry in years
// <df> discount factor (prize of zero coupon bond with expiry T)
// <F> forward of the options underlying asset for expiry T
// <sigma> underlying's  volatility
// returns (discounted)  option's price
//
double bs_price(bool isCall, double K, double T, 
               double df, double F, double sigma);

//
// Black Scholes pricing formula:
// European option  forward (discounted) price as a function of
//    the explict market data
// <isCall> true for calls , false for puts
// <K> option strike  
// <T> option expiry in years
// <S> spot price of the underlying asset
// <r> zero coupon discount rate 
// <d> stock dividend yield
// <sigma> underlying's  volatility
// returns (discounted)  option's price
//
double bs_price(bool isCall, double K, double T, 
               double S, double r, 
               double d, double sigma);




//
// Black Scholes price and risk formula:
// European option  forward (discounted) price and risk as a function of
//    the explict market data
// <isCall> true for calls , false for puts
// <K> option strike  
// <T> option expiry in years
// <S> spot price of the underlying asset
// <r> zero coupon discount rate 
// <d> stock dividend yield
// <sigma> underlying's  volatility
// 
// the function return value is the  (discounted)  option's price
// the function arguments delta, gamma, vega, rho are passed by reference
// and are set to the option's greeks
//
double bs_risk(bool isCall, double K, double T, 
               double S, double r, 
               double d, double sigma,
               double &delta, double &gamma, double &vega, double &rho) {

    // Discount factor and forward price
    const double df   = discount(T, r);        // e^{-rT}
    const double F    = forward(T, S, r, d);   // S e^{(r-d)T}
    const double sqrtT = std::sqrt(T);

    // d1, d2
    const double x   = std::log(F / K);
    const double ds  = sigma * sqrtT;
    const double d2  = (x - 0.5 * ds * ds) / ds;
    const double d1  = d2 + ds;

    // Option price (reuse existing pricing function)
    const double price = bs_price(isCall, K, T, df, F, sigma);

    // Common multiplier for greeks
    const double qdf = std::exp(-d * T); // dividend discount factor

    if (isCall) {
        delta = qdf * ndtr(d1);
        gamma = qdf * nphi(d1) / (S * ds);
        vega  = qdf * S * nphi(d1) * sqrtT;
        rho   = K * df * T * ndtr(d2);
    } else {
        delta = qdf * (ndtr(d1) - 1.0);
        gamma = qdf * nphi(d1) / (S * ds);
        vega  = qdf * S * nphi(d1) * sqrtT;
        rho   = -K * df * T * ndtr(-d2);
    }

    return price;

}