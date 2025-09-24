#pragma once

// 
// compute linearly interpolated discount factor at time t
// given:
//     <t>: time in years to discount to
//     <tenors>:  size of <Ts> and <rs> arrays
//     <Ts>: array expiry tenors in years.
//           <Ts> must be sorted in ascending order
//     <rs>: array of zero coupon rates for expiries <Ts>
//
double discount(double t, int tenors, 
                const double *Ts, const double *rs);

//
// compute the present value of a bond
// given:
// Bond defintion:  
//     <T>: time in years to maturity
//     <coupon>: coupon rate
//     <freq>: coupon frequency in years
// Discount curve definition:
//     <tenors>:  size of <Ts> and <rs> arrays
//     <Ts>: array expiry tenors in years.
//           <Ts> must be sorted in ascending order
//     <rs>: array of zero coupon rates for expiries <Ts>
// 
double bond_pv(double T,double coupon, double freq,
            int tenors, const double *Ts, const double *rs);
//
// compute the swap rate
// given:
// Swap definition:
//     <T>: time in years to maturity
//     <freq>: coupon frequency in years
// Discount curve definition:
//     <tenors>:  size of <Ts> and <rs> arrays
//     <Ts>: array expiry tenors in years.
//           <Ts> must be sorted in ascending order
//     <rs>: array of zero coupon rates for expiries <Ts>
//
double swap_rate(double T, double freq, 
            int tenors, const double *Ts, const double *rs);

//
// compute the present value of a swap
// given:
// Swap definition:
//     <is_receiver>: true if receiver, false if payer
//     <R>: swap rate
//     <T>: time in years to maturity
//     <freq>: coupon frequency in years
// Discount curve definition:
//     <tenors>:  size of <Ts> and <rs> arrays
//     <Ts>: array expiry tenors in years.
//           <Ts> must be sorted in ascending order
//     <rs>: array of zero coupon rates for expiries <Ts>
//
double swap_pv(bool is_receiver,double R, double T, double freq, 
               int tenors, const double *Ts, const double *rs);
