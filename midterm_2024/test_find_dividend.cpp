
#include <iostream>

using namespace std;

#include "discount.h"
#include "forward.h"
#include "solve.h"

//
// Compute difference between the theoretical forward price and market forward price
//
// inputs:
//   <d>: dividend yield for the index tenor
//   <size>: size of the <params> array must be 3+3*<tenors>
//   <params>: array of parameters
//            <params[0]>: index of the tenor for which the dividend yield is being computed
//            <params[1]>: market forward price for that tenor
//            <params[2]>: spot price of the underlying asset
//            <params[3+i]>: expiry tenor in years for the ith tenor, for <tenors> tenors
//            <params[3+tenors+i]>: zero coupon discount rate for the ith tenor, for <tenors> tenors 
//            <params[3+2*tenors+i]>: dividend yield for the ith tenor, for <tenors> tenors
//                   function will set <params[3+2*tenors+index]> to <d> before computing the forward price
// output:
//   difference between the theoretical forward price and market forward price
//
double forward_function(double d, int size, double *params) {
    int index= params[0];
    double F=params[1];
    double S=params[2];
    
    int tenors=(size-3)/3;
    double* Ts=params+3;
    double *rs=params+3+tenors;
    double *ds=params+3+2*tenors;
    double T=Ts[index];
    ds[index]=d;
    
    return forward(T,S,tenors,Ts,rs,ds)-F;
}

// 
// Find the dividend yield for a forward price given the market data for a single tenor <index
//
// inputs:
//   <index>: index of the tenor for which the dividend yield is being computed
//   <F>: market forward price for that tenor
//   <size>: size of the <params> array must be 3+3*<tenors>
//   <params>: array of parameters
//            <params[0]>: will be set by the function to <index>
//            <params[1]>: will be set by the function to the market forward price for that tenor
//            <params[2]>: spot price of the underlying asset
//            <params[3+i]>: expiry tenor in years for the ith tenor, for <tenors> tenors
//            <params[3+tenors+i]>: zero coupon discount rate for the ith tenor, for <tenors> tenors
//            <params[3+2*tenors+i]>: dividend yield for the ith tenor, for <tenors> tenors
//                   function will set <params[3+2*tenors+index]> to the dividend yield before returning
//   <max_iter>: maximum number of iterations for the bisection algorithm
//   <tol>: tolerance for the bisection algorithm
// output:
//   <dividend>: dividend yield for the tenor <index> that makes the theoretical forward price equal to <F>
// return:
//   0 if the dividend yield is found
//   1 if the dividend yield is not found
//
int find_dividend(int index, double F, int size, double *params, int max_iter, double tol, double & dividend) { 
    params[0]=index;
    params[1]=F;
    double x0=0;
    double x1=0.5;
    double x=0.1;
    return solve_bisection(x,x0,x1,forward_function,size,params,max_iter,tol,dividend);
}

int bootstrap_dividends(double S, 
                        int tenors, 
                        const double *Ts, 
                        const double *rs, 
                        const double* Fs, 
                        int max_iter, 
                        double tol, 
                        double *ds,
                        int &index) {
    int size=3+3*tenors;
    double *params=new double[size];
    params[0]=0;  // to be set later
    params[1]=0;  // to be set later
    params[2]=S;  // spot price
    for(int i=0;i<tenors;i++) {
        params[3+i]=Ts[i];
        params[3+tenors+i]=rs[i];
        params[3+2*tenors+i]=0; // to be set later
    }
    for(index=0;index<tenors;index++) {
        double F=Fs[index];
        double dividend;
        int  result=find_dividend(index,F, size, params, max_iter,  tol, dividend);
        if(result!=0) {
            delete[] params;
            return result;
        }
        ds[index]=dividend;
    }
    delete[] params;
    return 0;
}

int main() {

    // Market Data
    double Ts[]={0.25,0.5,1, 2,3,5};
    double rs[]={0.045,0.04,0.035,0.035,0.0375,0.04};
    double S=100;
    const int tenors=sizeof(Ts)/sizeof(Ts[0]);

    int max_iter=100;
    double tol=1e-8;

    double Fs[][tenors]={{100.1, 101.5, 102, 102.5, 103, 106},
                            {101, 102.5, 103, 104, 105, 107},
                            {102.1, 101.5, 102, 102.5, 103, 106},
                            {100.1, 101.5, 107, 107.5, 108, 1011},
                            {100.0, 90., 80, 60., 40, 10},
                            {100.15, 101.7, 102.3, 103, 104, 107}};

    
    int status;
    double ds[tenors];
    const int tests=sizeof(Fs)/sizeof(Fs[0]);
    for (int test=0;test<tests;test++) {
        cout<<"Test "<<test<<": ";
        int index;
        status=bootstrap_dividends(S,
             tenors, Ts, rs, Fs[test],    
             max_iter, tol, 
             ds, index);
        if(status!=0) {
            if (status==1) {
                cout<<"Zero not bracketed at tenor "<< Ts[index]<<" forward "<<Fs[test][index]<<endl;
                continue;
            } else if (status==2) {
                cout<<"Maximum number ot iterations reached at  tenor "<< Ts[index]<<" forward "<<Fs[test][index]<<endl;
                continue;
            }
            else {  cout<<"Failed to bootstrap dividends"<<endl;
                continue;
            }
        }
        cout<<endl;
        for (int i=0;i<tenors;i++) {
            double f=forward(Ts[i],S,tenors,Ts,rs,ds);
            cout<<Ts[i]<<","<<ds[i]<<","<<Fs[i][i]<<","<<f<<","<< Fs[i][i]-f <<endl; 
        }
    }
    return 0;
}