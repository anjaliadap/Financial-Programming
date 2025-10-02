#include <cmath>
#include "volatility.h"
#include "black_scholes.h"
#include "discount.h"
#include "forward.h"

using namespace std;

double volatility(double t
                    , int tenors
                    , const double *Ts
                    , const double *sigmas) {
    
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

// Problem 2.1 + 2.2
int volatility_bootstrap(int tenors,
                         const bool *is_call,
                         const double *Ks,
                         const double *Ts,
                         double S,
                         const double *rs,     // zero curve (continuous) for discount()
                         const double *ds,     // dividend curve (continuous) for forward()
                         const double *prices, // market *discounted* prices
                         double *sigmas,       // output implied vols
                         int max_iter, double tol)
{
    // ---- 2.1: solve implied vol at each tenor ----
    for (int i = 0; i < tenors; ++i) {
        const double T = Ts[i];
        const double K = Ks[i];

        if (!(T > 0.0) || !(S > 0.0) || !(K > 0.0)) {
            // bad inputs at tenor i
            return i + 1;  // positive => failure at index i
        }

        // discount factor and forward at T
        double df = discount(T, tenors, Ts, rs);                
        double F  = forward(T, S, tenors, Ts, rs, ds);          

        if (!(df > 0.0)) { return i + 1; }

        // Convert market price (discounted) to *forward* price
        const double price_fwd = prices[i] / df;

        double sigma = 0.0;
        int status = bs_implied_vol(
            is_call[i],   // call/put flag
            K, T,
            F,            // forward
            price_fwd,    // *undiscounted* option price
            sigma,
            max_iter, tol
        );

        if (status != 0 || !(sigma == sigma)) {   // also catch NaN
            return i + 1;  // solver failed at tenor i
        }

        sigmas[i] = sigma;
    }

    // ---- 2.2: no-arbitrage check: variance*time must be nondecreasing ----
    // require: for T'>T,  sigma(T')^2 * T'  >=  sigma(T)^2 * T
    const double eps = 1e-14;  // tiny tolerance
    for (int i = 1; i < tenors; ++i) {
        if (!(Ts[i] > Ts[i-1])) {
            // expiries must be strictly increasing
            return -1;  // arbitrage / bad tenor ordering
        }
        const double v_prev = sigmas[i-1] * sigmas[i-1] * Ts[i-1];
        const double v_curr = sigmas[i]   * sigmas[i]   * Ts[i];
        if (v_curr + eps < v_prev) {
            return -1;  // calendar-spread arbitrage
        }
    }

    return 0;  // success
}
