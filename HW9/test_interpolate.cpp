#include "interpolate.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int main() {
    std::vector<double> xs = {0.0, 1, 2, 3, 4};
    std::vector<double> ys = {1.0, 3, 5, 7, 9};
    std::vector<double> x_test = {-1, -0.5, 0, 0.5, 1, 3.5, 4, 4.5};

    for (double x : x_test) {
        double y_interp = interpolate(x, xs, ys);
        double y_expected = std::max(1.0, std::min(9.0, 1.0 + 2.0 * x));
        bool ok = std::abs(y_interp - y_expected) < 1e-12;
        std::cout << "x=" << x
                  << "  interp=" << y_interp
                  << "  expected=" << y_expected
                  << "  " << (ok ? "yes" : "no")
                  << '\n';
    }
    return 0;
}
