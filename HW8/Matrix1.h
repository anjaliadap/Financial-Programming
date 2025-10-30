// Matrix1.h
#pragma once
#include <iostream>
#include "VectorDouble.h"

class Matrix1 {
private:
    size_t m_rows;
    size_t m_cols;
    VectorDouble m_data;   // replaces double* m_data

public:
    Matrix1(size_t rows = 0, size_t cols = 0)
        : m_rows(rows), m_cols(cols), m_data(rows * cols)
    {
        std::cerr << "Calling Matrix1 constructor" << std::endl;
    }

    ~Matrix1() {
        std::cerr << "Calling Matrix1 destructor" << std::endl;
    }

    size_t rows() const { return m_rows; }
    size_t cols() const { return m_cols; }

    double& operator()(size_t r, size_t c) {
        return m_data[r * m_cols + c];
    }

    const double& operator()(size_t r, size_t c) const {
        return m_data[r * m_cols + c];
    }

    Matrix1 transpose() const;
};