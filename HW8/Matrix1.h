#pragma once
#include "VectorDouble.h"
#include <iostream>
#include <stdexcept>
#include <format>

class Matrix1 {
private:
    size_t m_rows;
    size_t m_cols;
    VectorDouble m_data;

public:
    // Constructor
    Matrix1(size_t rows, size_t cols)
        : m_rows(rows), m_cols(cols), m_data(rows * cols)
    {
        //std::cerr << "Calling Matrix constructor\n";
    }

    size_t rows() const { return m_rows; }
    size_t cols() const { return m_cols; }

    inline double& operator[](size_t row, size_t col) {
        return m_data[m_cols * row + col];
    }

    inline double operator[](size_t row, size_t col) const {
        return m_data[m_cols * row + col];
    }

    Matrix1 transpose() const;
    VectorDouble operator*(const VectorDouble& x) const;
    Matrix1 operator*(const Matrix1& M) const;
};
