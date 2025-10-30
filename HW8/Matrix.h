#pragma once
#include "VectorDouble.h"
#include <iostream>
#include <stdexcept>
#include <format>

class Matrix {
private:
    size_t m_rows;
    size_t m_cols;
    double* m_data;

public:
    // Constructor
    Matrix(size_t rows, size_t cols)
        : m_rows{rows}, m_cols{cols}, m_data(nullptr)
    {
        //std::cerr << "Calling Matrix constructor\n";
        m_data = new double[m_rows * m_cols];
    }

    // Destructor
    ~Matrix() {
        //std::cerr << "Calling Matrix destructor\n";
        delete[] m_data;
    }

    // Copy constructor
    Matrix(const Matrix& other)
        : m_rows(other.m_rows), m_cols(other.m_cols)
    {
        std::cerr << "Calling Matrix copy constructor\n";
        m_data = new double[m_rows * m_cols];
        for (size_t i = 0; i < m_rows * m_cols; ++i)
            m_data[i] = other.m_data[i];
    }

    // Copy assignment
    Matrix& operator=(const Matrix& other) {
        std::cerr << "Calling Matrix copy assignment\n";
        if (this == &other) return *this; // protect self-assignment

        // Allocate new memory and copy
        double* new_data = new double[other.m_rows * other.m_cols];
        for (size_t i = 0; i < other.m_rows * other.m_cols; ++i)
            new_data[i] = other.m_data[i];

        // Free old and replace
        delete[] m_data;
        m_data = new_data;
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        return *this;
    }

    // Move constructor
    Matrix(Matrix&& other) noexcept
        : m_rows(other.m_rows), m_cols(other.m_cols), m_data(other.m_data)
    {
        std::cerr << "Calling Matrix move constructor\n";
        other.m_rows = other.m_cols = 0;
        other.m_data = nullptr;
    }

    // Move assignment
    Matrix& operator=(Matrix&& other) noexcept {
        std::cerr << "Calling Matrix move assignment\n";
        if (this == &other) return *this;

        delete[] m_data;
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_data = other.m_data;

        other.m_rows = other.m_cols = 0;
        other.m_data = nullptr;
        return *this;
    }

    size_t rows() const { return m_rows; }
    size_t cols() const { return m_cols; }

    inline double& operator[](size_t row, size_t col) {
        return m_data[m_cols * row + col];
    }
    inline double operator[](size_t row, size_t col) const {
        return m_data[m_cols * row + col];
    }

    Matrix transpose() const;
    VectorDouble operator*(const VectorDouble& x) const;
    Matrix operator*(const Matrix& M) const;
};
