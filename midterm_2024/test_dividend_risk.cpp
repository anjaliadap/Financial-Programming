#include <cmath>

#include "discount.h"
#include "forward.h"
#include "volatility.h"
#include "black_scholes.h"

#include <iostream>

using namespace std;

double find_analytical_dividend(double T, double F, double S, int tenors, double *Ts, double *rs) { 
    double df=discount(T,tenors,Ts, rs);
    return -log (F/S*df)/T;
}

void bootstrap_analytical_dividends(double S, 
                                    int tenors, 
                                    double *Ts, 
                                    double *rs, 
                                    double* Fs, 
                                    double *ds) {
    for(int i=0;i<tenors;i++) {
        double T=Ts[i];
        double F=Fs[i];
        ds[i]=find_analytical_dividend(T,F,S,tenors,Ts,rs);
    }
}

// PROBLEM 4.1
//
// Compute the market value of a portfolio of options using Black-Scholes formula
//
// inputs:
//   <options>: number of options in the portfolio
//   <notionals>: array of notionals for each option, must be of size <options>
//   <is_calls>: array of option kinds: of true for calls, false for puts, must be of size <options>
//   <Ks>: array of option strikes, must be of size <options>
//   <T_exps>: array of option expiries (in years) must be of size <options>
//   <S>: spot price of the underlying asset
//   <tenors>:  size of <Ts>, <rs>  <ds> and <sigmas> arrays
//   <Ts>: array expiry tenors in years.
//            <Ts> must be sorted in ascending order
//   <rs>: zero coupon discount rates
//   <ds>: stock dividend yields
//   <sigmas>: underlying's  volatility inputs
//            the implied variances must be increasing
// return:
//   the total value of the option portfolio using back_scholes pricing
//
double option_portfolio_value(int options, const double *notionals, 
                        const bool *is_calls, const double *Ks, const double *T_exps, 
                        double S, 
                        int tenors, 
                        const double *Ts, const double *rs, 
                        const double *ds, const double *sigmas) {
   double value=0;
    for(int i=0;i<options;i++) {
        value+=notionals[i]*bs_price(is_calls[i],Ks[i],T_exps[i],S,tenors,Ts,rs,ds,sigmas);       
    }
    return value;
}

// PROBLEM 4.3
//
// Compute the dividend risk of a portfolio of options using Black-Scholes formula
//
// Dividend risk is the change in the value of the portfolio for a 0.01% change  in the dividend yield
// at each expiry tenor
//
// inputs:
//   <options>: number of options in the portfolio
//   <notionals>: array of notionals for each option, must be of size <options>
//   <is_calls>: array of option kinds: of true for calls, false for puts, must be of size <options>
//   <Ks>: array of option strikes, must be of size <options>
//   <T_exps>: array of option expiries (in years) must be of size <options>
//   <S>: spot price of the underlying asset
//   <tenors>:  size of <Ts>, <rs>  <ds> and <sigmas> arrays
//   <Ts>: array expiry tenors in years.
//            <Ts> must be sorted in ascending order
//   <rs>: zero coupon discount rates
//   <ds>: stock dividend yields
//   <sigmas>: underlying's  volatility inputs
//            the implied variances must be increasing
// output:
//   <risk>: array will be populated with  dividend risk for each tenor in Ts, must be of size <tenors>
//

void option_portfolio_dividend_risk(int options, const double *notionals, const bool *is_calls,
                        const double *Ks, const double *T_exps, 
                        double S, 
                        int tenors, const double *Ts, const double *rs, 
                        const double *ds, const double *sigmas, double *risk) {
    double value0=option_portfolio_value(options,notionals,is_calls, Ks,T_exps,S,tenors,Ts,rs,ds,sigmas);

    double *ds1=new double[tenors];
    for (int i1=0;i1<tenors;i1++) {
            ds1[i1]=ds[i1];
    }  
    for(int i1=0;i1<tenors;i1++) {   
        ds1[i1]+=0.0001;
        double value1=option_portfolio_value(options,notionals,is_calls, Ks,T_exps,S,tenors,Ts,rs,ds1,sigmas);
        risk[i1]=(value1-value0);
        ds1[i1]=ds[i1]; // restore dividend yield
    }
}

int main() {
   
    // Option Data
    const int options=5;
    double notionals[options]={1000,4000,-4000,-1000,1000};
    bool is_calls[options]={true,true,false,false,true};
    double Ks[options]={6000,6200,6200,6000,6700};
    double T_exps[options]={0.5,1.75,1.75,2.75,3.5};

    // Market Data
    double S=6000;
    const int tenors=7;
    double Ts[tenors]={0.25,0.5,1, 2,3,5,10};
    double rs[tenors]={0.045,0.04,0.035,0.035,0.0375,0.04,0.045};
    double Fs[tenors]={6050,6080,6120,6230,6380,6700,7800};
    double sigmas[tenors]={0.2,0.2,0.2,0.2,0.2,0.2,0.2};


    
    // PROBLEM 4.3
    double ds[tenors];
    bootstrap_analytical_dividends(S, tenors, Ts, rs, Fs, ds);
    
    double value=option_portfolio_value(options, notionals, is_calls, Ks, T_exps, S, tenors, Ts, rs, ds, sigmas);
    cout<<"Portfolio value: "<<value<<endl;

    double risk[tenors];
    option_portfolio_dividend_risk(options, notionals, is_calls, Ks, T_exps, S, tenors, Ts, rs, ds, sigmas, risk);
    cout<<"Portfolio dividend risk: "<<endl;
    for (int i=0;i<tenors;i++) {
        cout<<"\t"<< Ts[i]<<","<<ds[i]<<","<<risk[i]<<endl; 
    }
    return 0;

}