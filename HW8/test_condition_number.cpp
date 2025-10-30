#include <cmath>
#include <iomanip>
#include <iostream>

#include "Matrix.h"
#include "VectorDouble.h"
#include "cholesky.h"

static double kappa_corr_2x2(double rho) {
    return (1.0 + rho) / (1.0 - rho);
}

static double norm2(const VectorDouble &v) {
    double s = 0.0;
    for (std::size_t i = 0; i < v.size(); ++i)
        s += v[i] * v[i];
    return std::sqrt(s);
}

int main() {
    const double eps = 0.01;
    const double rhos[] = {0.9, 0.99, 0.999, 0.9999};

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "rho, kappa, max_error_bound, actual_error\n";

    for (double rho : rhos) {
        Matrix C(2, 2);
        C(0,0) = 1.0;  C(0,1) = rho;
        C(1,0) = rho;  C(1,1) = 1.0;

        VectorDouble b(2), bp(2);
        b[0]  = 0.5;        b[1]  = 0.5;
        bp[0] = 0.5 + eps;  bp[1] = 0.5;

        Matrix L = cholesky_decomposition(C);
        VectorDouble w  = solve_cholesky(L, b);
        VectorDouble wp = solve_cholesky(L, bp);

        VectorDouble diff = wp - w;
        double actual_error = std::sqrt(2.0) * norm2(diff); // ✅ fixed
        double kappa = kappa_corr_2x2(rho);
        double max_error_bound = kappa * eps;

        std::cout << rho << ", "
                  << kappa << ", "
                  << max_error_bound << ", "
                  << actual_error << "\n";
    }

    return 0;
}