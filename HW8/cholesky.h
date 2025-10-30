#pragma once
#include <cmath>
#include <format>

#include <exception>
#include <stdexcept>


#include "Matrix.h"
#include "VectorDouble.h"


// Compute the Cholesky decomposition of a positive-definite matrix A
//
// Given a symmetric, positive-definite matrix A, this function computes
// a lower triangular matrix L such that 
//
//      A = L * L^T
//
// If the matrix is not positive-semi definite, an exception is thrown.
// If the matrix is not square, an exception is thrown.
//
Matrix cholesky_decomposition(const Matrix& A);  

// Solve the linear system Ax=b using the Cholesky factorization of A
// Given a lower triangular matrix L such that
//      A=L*L^T,
// this function  the linear system
//      A x = b
// using forward and backward substitution.
//      L y =   b (solve y by forward substitution)
//      L^T x = y (solve x by backward substitution)
//
// Returns the solution vector x
// Remarks: Use cholesky_decomposition(A) to compute L from A.
//
VectorDouble solve_cholesky(const Matrix &L, VectorDouble b);