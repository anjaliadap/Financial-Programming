#include <cmath>

#include "discount.h"
#include "forward.h"

#include <iostream>


using namespace std;

// PROBLEM 2.1
double find_analytical_dividend(double T, double F, double S, int tenors, const double *Ts, const double *rs) { 
    double df=discount(T,tenors,Ts, rs);
    return -log (F/S*df)/T;
}

// PROBLEM 2.2
void bootstrap_analytical_dividends(double S, 
                                    int tenors, 
                                    const double *Ts, 
                                    const double *rs, 
                                    const double* Fs, 
                                    double *ds) {
    for(int i=0;i<tenors;i++) {
        double T=Ts[i];
        double F=Fs[i];
        ds[i]=find_analytical_dividend(T,F,S,tenors,Ts,rs);
    }
}

// PROBLEM 2.4
int test_forwards(int ntests,double *test_Ts, double *test_Fs,
  double S, int tenors, const double *Ts, const double *rs,const  double *ds, double tol, int &index) {
    for (index=0;index<ntests;index++) {
        double T=test_Ts[index];
        double F=forward(T,S,tenors,Ts,rs,ds);
        if (abs(F-test_Fs[index])>tol) {
            return 1;
        }
    }
    return 0;
  }

int main() {
   
    double S=6000;
    const int tenors=7;
    double Ts[tenors]={0.25,0.5,1, 2,3,5,10};
    double rs[tenors]={0.045,0.04,0.035,0.035,0.0375,0.04,0.045};
   
    // PROBLEM 2.3
    double Fs[tenors]={6050,6080,6120,6230,6380,6700,7800};
    
    double ds[tenors];
    bootstrap_analytical_dividends(S, tenors, Ts, rs, Fs, ds);
    cout<<"Analytical dividends"<<endl;
    for (int i=0;i<tenors;i++) {
        double f=forward(Ts[i],S,tenors,Ts,rs,ds);
        cout<<"\t"<< Ts[i]<<","<<ds[i]<<","<<Fs[i]<<","<< Fs[i]-f <<endl; 
    }

    // PROBLEM 2.4
     double test_Ts[]={0.25,0.5,0.75,1,1.25,1.5,1.75, 2,2,25,2.5,2.27, 3,4,5,6,7,8,9,10};
    double test_Fs[]={6050,6080,6105.0688,6120,6148.4626,6176.29,6203.4723,
                      6230,6230,11561.379,6301.9363,6268.0964,6380,6532.814,
                      6700,6883.8447,7084.5321,7303.2326,7541.2431,7800};
    double tol=1e-3;

    const int ntests=sizeof(test_Ts)/sizeof(test_Ts[0]); 
    int index;
    int status=test_forwards(ntests, test_Ts, test_Fs, S, tenors, Ts, rs, ds, tol, index);
    if (status==0) {
        cout<<"Forward Test  passed"<<endl;
    } else {
        cout<<"Forward Test failed at index " <<index <<endl;
        return 1;
    }   
    return 0;
}