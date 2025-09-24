#pragma once
//
// compute stock forward 
// given:
//      <T>: time in years to maturity of forward
//      <S>: spot price of stock
//      <tenors>:  size of <Ts>, <rs>  <ds> arrays
//      <Ts>: array expiry tenors in years.
//            <Ts> must be sorted in ascending order
//      <rs>: array of zero coupon rates for expiries <Ts>
//      <ds>: array of dividend yields for expiries <Ts>
//
double forward(double T, double S, 
              int tenors,  const double *Ts, 
              const double *rs, const double *ds);