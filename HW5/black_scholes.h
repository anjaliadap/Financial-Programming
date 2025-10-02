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
// given:
//   Option definition:
//      <isCall> true for calls, false for puts
//      <K> option strike  
//      <T> option expiry in years
//   Market data:
//      <S> spot price of the underlying asset
//      <tenors>:  size of <Ts>, <rs>  <ds> and <sigmas> arrays
//      <Ts>: array expiry tenors in years.
//            <Ts> must be sorted in ascending order
//      <rs> zero coupon discount rates 
//      <ds> stock dividend yields
//      <sigmas> underlying's  volatility inputs
//            the implied variances must be increasing
// returns (discounted)  option's price
//      rates and dividends are linearly interpolated,
//      volatility is interpolated in variance space
//
double bs_price(bool is_call, double K, double T, 
    double S, int tenors, const double *Ts, 
    const double *rs, const double *ds, const double *sigmas);

//
// compute implied volatility give option forward price              
//
// given:
//   Option definition:
//      <isCall> true for calls, false for puts
//      <K> option strike
//      <T> option expiry in years
//   Market Data:
//      <F> forward price of the underlying asset
//      <price_fwd> option forward price
//   Calibrator inputs:
//      max_iter: maximum number of iterations
//      tol: tolerance for the solver
// returns:
//      <sigma>: implied volatility that makes Black Scholes
//              option price equal to <price_fwd>
//

int bs_implied_vol(bool is_call,double K, double T, 
                   double F, double price_fwd, 
                   double & sigma, 
                   int max_iter=100, double tol=1e-8);

// 
// Bootstrap volatility curve from option prices
//
// given:
//   Options definition:
//      <tenors> size of inputs,  <Ks>, <is_call>, <Ts>, <rs>, <ds> and <prices> arrays
//      <is_call>: array of booleans, true for calls, false for puts
//      <Ks>: array of option strikes
//      <Ts>: array of option expiries in years
//   Market Data:
//      <rs>: array of zero coupon discount rates, for maturities <Ts>
//      <ds>: array of stock dividend yields
//      <prices>: array of discounted option prices
//   Calibrator inputs:
//      max_iter: maximum number of iterations
//      tol: tolerance for the solver
// output:
//      <sigmas>: array of implied volatilities
//          such that option prices computed from <sigmas> match input <prices>
// returns:
//      0 if successful, non-zero if failed
//          a positive error code means that the solver failed to converge
//          a negative error code means that the volatility curve has an arbitrage.
//
int volatility_bootstrap(int tenors,  
                         const bool * is_call, const double *Ks, const double *Ts,
                         double S, const double * rs, const double *ds,
                         const double *prices,
                         double *sigmas, 
                         int max_iter=100, double tol=1e-8);