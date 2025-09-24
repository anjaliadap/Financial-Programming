#include <iostream>
#include "black_scholes.h"
using namespace std;

int main() {
    
    int  units[]={1000,1000,-1000,-1000};
    bool is_call[]={true,false,true,false};
    double K[]={110,90,120,80};
    double T[]={1.0,1.0,1.5,1.5};
    int noptions=sizeof(units)/sizeof(double);

    double S=100.0;
    double tenors;
    double Ts[]={1.0,2.0,5.0};  
    double rs[]={0.055,0.0525,0.05};
    double ds[]={0.0125,0.015,0.0175};
    double sigmas[]={0.25,0.26,0.265};
    tenors=sizeof(Ts)/sizeof(double);

    // Allocate Space for the Greeks per option (Problem 3.1)

    // compute risk for each option (Problem 3.2)

    // output greeks per option (Problem 3.3)

    // compute total results (Problem 3.4)
    
    // output total greeks (Problem 3.5)

    return 0;
}   