#pragma once

//
// compute interpolated volatility at time t
// given:   
//     <t>: time in years to maturity of option
//     <tenors>:  size of <Ts> and <sigmas> arrays
//     <Ts>: array expiry tenors in years.
//           <Ts> must be sorted in ascending order
//     <sigmas>: array of volatilities for expiries <Ts>
//
//  Interpolation is linear on variance, not volatility
//
double volatility(double t, int tenors, 
          const double *Ts, const double *sigmas);
