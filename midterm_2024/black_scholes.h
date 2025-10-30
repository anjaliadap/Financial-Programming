#pragma once
extern int bs_count; // count the number of times bs_price is called
extern int dbs_count; // count the number of times bs_dprice is called

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
// bs_implied_vol: compute implied volatility given 
//                 forward option price                
//
int bs_implied_vol(bool is_call,double K, double T, 
                   double F, double price_fwd, 
                   double & sigma, 
                   int max_iter=100, double tol=1e-8);

