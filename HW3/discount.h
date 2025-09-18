#pragma once

//
// compute the discount factor (price of a zero-coupon bond)
// given the interest rate r and the time to expiry T in years
// 

double discount(double T, double r);
//
// compute the present value of a bond cash flows
// given level of interest rate r
// The bond is described by
//      T:       time to maturity of bond
//      coupon: annualized interest payment
//      freq:   coupon frequency, number of coupon payments per year
//

double bond_pv(double T,double coupon, double freq, double r);
// 
// compute the swap par rate given the level of interest rates r
//  the time to maturity T, and the frequency of payments freq
//

double swap_rate(double T, double freq,  double r);

// 
// compute the swap present value givent the inputs:
//         is_receiver: true if the swap is a receiver fix swap, false if it is a payer swap
//         R:           the swap  rate    
//         T:           the time to maturity of the swap
//         freq:        the frequency of payments of the swap
//         r:           the current level of interest rates (continuously compounded
//                          zero coupon rate)
//
double swap_pv(bool is_receiver, double R, double T, double freq,  double r);