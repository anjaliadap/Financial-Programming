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
               int tenors, const double *Ts, const  double *rs);


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

//
// Bootstrap discount curve zero coupon rates from swap rates
//
// given:
// Swap curve definition:
//     <tenors>:  size of <Ts> and <Rs> arrays
//     <Ts>: array expiry tenors in years.
//           <Ts> must be sorted in ascending order
//     <Rs>: array of swap rates for expiries <Ts>
//     <freq>: swap coupon frequency in years
//  Bootstrapping parameters:
//     <max_iter>: maximum number of iterations in solver
//     <tol>: tolerance for solver
// output:
//     <rs>: array of zero coupon rates for expiries <Ts>
//        such that swap rates computed from <rs> match <Rs>
//        for all expiries in <Ts>.
// returns:
//     0 if successful, non-zero if failed
//
int  swap_bootstrap(int tenors, const double *Ts, 
                    const double *Rs, double freq, 
                    double * rs,
                    int max_iter=100, double tol=1e-8);


int bond_bootstrap(int tenors, double *Ts, double *coupons, 
                   double *prices,double freq, double * rs,
                   int max_iter=100, double tol=1e-8);