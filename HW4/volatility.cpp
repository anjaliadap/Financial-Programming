#include <cmath>
#include "volatility.h"
using namespace std;
double volatility(double t, int tenors, 
         const double *Ts, const double *sigmas) {
    int index=0;
    while (index<tenors && Ts[index]<t) {
        index++;
    }
    double r;
    if (index==0) {
        return sigmas[0];
    } else if (index==tenors) {
        return sigmas[tenors-1];
    } else {;
        double sigma1=sigmas[index];
        double t1=Ts[index];
        int index0=index-1;
        double t0=Ts[index0];
        double sigma0=sigmas[index-1];
        // we interpolate on variance
        double var0=sigma0*sigma0*t0;
        double var1=sigma1*sigma1*t1;
        double dt=t-t0;
        double dvar=var1-var0;
        double var=var0+dvar*dt/(t1-t0);
        double sigma=sqrt(var/t);
        return sigma;
    }
}
