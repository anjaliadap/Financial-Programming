#include <cmath>
#include "discount.h"
#include "forward.h"
double forward(double T, double S, int tenors,
 const  double *Ts, const double *rs, const double *ds) {
    double df_r=discount(T,tenors,Ts, rs);
    double df_d=discount(T,tenors,Ts, ds);
    return S*df_d/df_r;
}