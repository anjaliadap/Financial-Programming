#include "cholesky.h"

#include <cmath>
#include <vector>
#include <cstddef>
#include <exception>
#include <stdexcept>
// Function to perform Cholesky decomposition
Matrix cholesky_decomposition(const Matrix& A) {
    if (A.rows()!=A.cols()) {
        throw std::runtime_error("Cholesky: Matrix must be square");
    }
    Matrix L=Matrix(A.rows(),A.cols());
    for (size_t row = 0; row < A.rows(); ++row) {
        for (size_t col = 0; col <= row; ++col) {
            double sum = 0;
            // Summation for diagonal elements
            if (row == col) {
                for (size_t k = 0; k < col; ++k) {
                    sum += L[col,k] * L[col,k];
                }
                if (A[col,col] - sum < 0) {
                    // Matrix is not positive-definite
                    std::string error_message=std::format("Cholesky: Matrix is not positive semi definite (negative or zero pivot on row {})",col);
                    throw std::runtime_error(error_message);
                }
                L[col,col] = std::sqrt(A[col,col] - sum);
            } else { // Summation for non-diagonal elements
                for (size_t k = 0; k < col; ++k) {
                    sum += L[row,k] * L[col,k];
                }
                L[row,col] = (A[row,col] - sum) / L[col,col];
            }
        }
    }
    return L;
}

// Function to solve Ax = b using Cholesky decomposition
VectorDouble solve_cholesky(const Matrix &L, VectorDouble b) {
    size_t D=L.rows();
    // forward solution of L y =b
    for (size_t col=0;col<D;col++) {
        double pivot=L[col,col];
        b[col]=b[col]/pivot;
        for (size_t row=col+1;row<D;row++) {
            b[row]-=L[row,col]*b[col];
        }
    }
    // backward solution of  L^T x = y
    for (size_t col=D;col-->0;) {
        double pivot=L[col,col];
        b[col]=b[col]/pivot;
        if (col==0) break;
        for (size_t row=col;row-->0;) {
            b[row]-=L[col,row]*b[col];
        }
    }
    return b;
}
