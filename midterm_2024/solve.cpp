#include "solve.h"
#include <cmath>
using namespace std;

int solve_bisection(double x, double x0, double x1, 
                    ParameterizedFunction function,
                    int size, double * params, 
                    int max_iter, double tol, double & result ) {
    double y0 = function(x0, size, params);
    double y1 = function(x1, size, params);
    if (y0*y1 > 0) {
        return 1; // Zero is not bracketed
    }
    double y = function(x, size, params);
    int iter = 0;
    while (iter < max_iter) {
        if (y*y0 < 0) {
            x1 = x;
            y1 = y;
        } else {
            x0 = x;
            y0 = y;
        }
        x = (x0 + x1)/2;
        y = function(x, size, params);
        if (abs(y) < tol) {
            result = x;
            return 0;
        }
        iter++;
    }
    return 2; // Max iterations exceeded
}
