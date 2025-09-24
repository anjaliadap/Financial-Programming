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
// Compute Risk of an option using Black Scholes formula
// given:
//   Option definition:
//      <is_call> true for calls, false for puts
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
// returns:
//       (discounted)  option's price as return value
//       delta by reference
//       gamma by reference
//       vega by reference
//       DV01 by reference
// 
double bs_risk(bool is_call, double K, double T, 
               double S, 
               int tenors, const double *Ts,const double *rs, 
               const double *ds, const double *sigmas,
               double &delta, double &gamma, double &vega, double &DV01);

//
// Compute Risk per option of an option portfolio using Black Scholes formula
// given:
//   Option definition:
//      <noptions> number of options in the portfolio
//      <units> array of option units
//      <is_call> array of booleans, true for calls, false for puts
//      <K> array of option strikes
//      <T> array of option expiries in years
//   Market data:
//      <S> spot price of the underlying asset
//      <tenors>:  size of <Ts>, <rs>  <ds> and <sigmas> arrays
//      <Ts>: array expiry tenors in years.
//            <Ts> must be sorted in ascending order
//      <rs> zero coupon discount rates
//      <ds> stock dividend yields
//      <sigmas> underlying's  volatility inputs
//            the implied variances must be increasing
// returns: all values are returned in arrays of size <noptions>,
//           one option greek per array element:
//       <value>:  array option values,  
//       <delta>:  array of option deltas,  
//       <gamma>:  array of option gammas, 
//       <vega>:   array vega of option vegas,
//       <DV01>:   array of option DV01s.
//    value, and all greeks are scaled  by the option's number of units
//
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
               double *delta, double *gamma, double *vega, double *DV01);

//
// Compute accumulated risk of a portfolio of options 
//  given:
//  Option greeks inputs:
//      <noptions> number of options in the portfolio
//      <values> array of option values 
//      <deltas> array of option deltas
//      <gammas> array of option gammas
//      <vegas> array of option vegas   
//      <DV01s> array of option DV01s
//    all arrays must be of size <noptions> 
//  returns:
//    sum of option values
//  additionally the function sets the following variables:
//    <delta>:  sum of deltas
//    <gamma>:  sum of gammas
//    <vega>:   sum of vegas
//    <DV01>:   sum of DV01s
//  by reference
//
double total_risk(
             int noptions, // risk inputs
                const double *values,
                const double *deltas,
                const double *gammas,
                const double *vegas,
                const double *DV01s,
                double &delta,  // risk outputs
                double &gamma, 
                double &vega, 
                double &DV01);