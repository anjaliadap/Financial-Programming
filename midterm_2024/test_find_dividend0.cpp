// INCLUDE HEADER FILES HERE


// PROBLEM 1.1
double forward_function(double d, // dividend yield
                        int size, double *params);


// PROBLEM 1.2
int find_dividend(int index, double F, 
                 int size, double *params, 
                 int max_iter, double tol, 
                 double & dividend);


// PROBLEM 1.3
int bootstrap_dividends(double S, 
                        int tenors, 
                        const double *Ts, 
                        const double *rs, 
                        const double* Fs, 
                        int max_iter, 
                        double tol, 
                        double *ds,
                        int &index);


int main() {
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
    
    // PROBLEM 1.4

     return 0;
 }