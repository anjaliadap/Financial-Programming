#include "cholesky.h"
#include "Matrix.h"          // or "Matrix1.h"
#include "VectorDouble.h"
#include <iostream>
#include <cmath>

int main() {
    std::cout << "rho,kappa,max_error,actual_error\n";

    double eps = 0.01;
    double rhos[] = {0.9, 0.99, 0.999, 0.9999};

    for (double rho : rhos) {
        // Build correlation matrix
        Matrix C(2, 2);
        C[0,0] = 1.0;   C[0,1] = rho;
        C[1,0] = rho;   C[1,1] = 1.0;

        // Define right-hand sides
        VectorDouble b(2);
        b[0] = 0.5; b[1] = 0.5;

        VectorDouble b2(2);
        b2[0] = 0.5 + eps; b2[1] = 0.5;

        // Compute Cholesky factorization
        Matrix L = cholesky_decomposition(C);

        // Solve systems
        VectorDouble w  = solve_cholesky(L, b);
        VectorDouble w2 = solve_cholesky(L, b2);

        // Compute condition number and errors
        double kappa = (1 + rho) / (1 - rho);
        double max_error = kappa * eps;
        double actual_error = std::sqrt(
            (w[0]-w2[0])*(w[0]-w2[0]) +
            (w[1]-w2[1])*(w[1]-w2[1])
        );

        std::cout << rho << "," << kappa << ","
                  << max_error << "," << actual_error << "\n";
    }

    return 0;
}
