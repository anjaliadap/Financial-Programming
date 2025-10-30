
 //INCLUDE HEADER FILES HERE

 // PROBLEM 4.1
double option_portfolio_value(int options,  // Option Data
                              const double *notionals, 
                              const bool *is_calls, 
                              const double *Ks, 
                              const double *T_exps, 
                              double S,  // Market Data
                              int tenors, 
                              const double *Ts, 
                              const double *rs, 
                              const double *ds, 
                              const double *sigmas); 
  

 // PROBLEM 4.2
void option_portfolio_dividend_risk(int options, // Option Data
                                    const double *notionals, 
                                    const bool *is_calls,
                                    const double *Ks, 
                                    const double *T_exps, 
                                    double S,  // Market Data
                                    int tenors, 
                                    const double *Ts, 
                                    const double *rs, 
                                    const double *ds, 
                                    const double *sigmas,
                                    double *risk // output
                                    );
    
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


    
    //PROBLEM 4.3
    
    return 0;

}