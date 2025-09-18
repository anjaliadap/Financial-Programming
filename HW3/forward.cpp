#include <cmath>
#include "forward.h"
double forward(double T, double S, double r, double d) {
    return S*std::exp((r-d)*T);
}