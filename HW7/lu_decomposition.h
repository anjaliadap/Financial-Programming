#pragma once

#include <cstddef>

// Simple Matrix class for demonstration purposes
class Matrix {
    private:
        size_t m_rows;
        size_t m_cols;
        double *m_data;
    public:
        Matrix(size_t rows,size_t cols, double *data):
            m_rows(rows),
            m_cols(cols),
            m_data(data) {}
        size_t rows() const { return m_rows; }
        size_t cols() const { return m_cols; }
        double operator[](size_t row, size_t col) const {
            return m_data[row*m_cols+col]; }
        double &operator[](size_t row, size_t col) {
            return m_data[row*m_cols+col]; }
};

// Matrix multiplication C = A * B
// A, B, C are square matrices of size D x D
//
void matrix_multiplication(const Matrix &A, const Matrix &B, 
                           Matrix &C);

// Matrix-vector multiplication result = A * v
// A is a square matrix of size D x D
// v is a vector of size D
// result is a vector of size D
//
void matrix_vector_multiplication(const Matrix &A, 
                                  double *v, double *result);

// Solve linear system of equation
//
//          A x = b 
//
// Using Gaussian elimination with partial pivoting
//
// A is a square matrix of size D x D
// b is a vector of size D
//
// The solution x is returned in b and A is modified during the process
//
void solve_linear_system(Matrix &A, double *b);

// LU decomposition of matrix A into L and U
// A is a square matrix of size D x D
// L is a lower triangular matrix of size D x D
// U is an upper triangular matrix of size D x D
//
void lu_decomposition(const Matrix &A, 
                      Matrix &L, Matrix &U);

// Solve lower triangular system of equation by using forward substitution
//
//          L x  = b 
//
// Remark: Solution is returned in place in vector b
void solve_forward(const Matrix &L, double *b);

// Solve upper triangular system of equation by using backward substitution
//
//          U x  = b
//
// Remark: Solution is returned inplace in vector b
void solve_backward(const Matrix &U, double *b);

// Solve linear system of equation
//
//      A x = b
//
//  Using LU decomposition
//
// Inputs:
//     L is a lower triangular matrix of size D x D
//     U is an upper triangular matrix of size D x D
//     b is a vector of size D
//
// L and U are obtained from the LU decomposition of A
//
//                A = L U
//
// The solution x is returned in b
//
void solve_lu(const Matrix &L, const Matrix &U, 
              double *b);


