// Matrix.h
#pragma once
#include <iostream>
#include <stdexcept>

class Matrix {
private:
    size_t m_rows;
    size_t m_cols;
    double* m_data;

public:
    Matrix(size_t rows = 0, size_t cols = 0);
    ~Matrix();

    // special member functions
    Matrix(const Matrix& other);            // copy ctor
    Matrix& operator=(const Matrix& other); // copy assignment
    Matrix(Matrix&& other);                 // move ctor
    Matrix& operator=(Matrix&& other);      // move assignment

    size_t rows() const { return m_rows; }
    size_t cols() const { return m_cols; }

    double& operator()(size_t r, size_t c);
    const double& operator()(size_t r, size_t c) const;

    Matrix transpose() const;
};