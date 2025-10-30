// Matrix.cpp
#include "Matrix.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Matrix::Matrix(size_t rows, size_t cols)
    : m_rows(rows), m_cols(cols) {
    cerr << "Calling Matrix constructor\n";
    m_data = new double[m_rows * m_cols];
}

Matrix::~Matrix() {
    cerr << "Calling Matrix destructor\n";
    delete[] m_data;
}

// Copy constructor
Matrix::Matrix(const Matrix& other)
    : m_rows(other.m_rows), m_cols(other.m_cols) {
    cerr << "Calling Matrix copy constructor\n";
    m_data = new double[m_rows * m_cols];
    for (size_t i = 0; i < m_rows * m_cols; ++i)
        m_data[i] = other.m_data[i];
}

// Copy assignment
Matrix& Matrix::operator=(const Matrix& other) {
    cerr << "Calling Matrix copy assignment\n";
    if (this == &other) return *this;
    delete[] m_data;
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_data = new double[m_rows * m_cols];
    for (size_t i = 0; i < m_rows * m_cols; ++i)
        m_data[i] = other.m_data[i];
    return *this;
}

// Move constructor
Matrix::Matrix(Matrix&& other)
    : m_rows(other.m_rows), m_cols(other.m_cols), m_data(other.m_data) {
    cerr << "Calling Matrix move constructor\n";
    other.m_data = nullptr;
    other.m_rows = other.m_cols = 0;
}

// Move assignment
Matrix& Matrix::operator=(Matrix&& other) {
    cerr << "Calling Matrix move assignment\n";
    if (this == &other) return *this;
    delete[] m_data;
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_data = other.m_data;
    other.m_data = nullptr;
    other.m_rows = other.m_cols = 0;
    return *this;
}

double& Matrix::operator()(size_t r, size_t c) {
    if (r >= m_rows || c >= m_cols)
        throw runtime_error("Matrix index out of range");
    return m_data[r * m_cols + c];
}

const double& Matrix::operator()(size_t r, size_t c) const {
    if (r >= m_rows || c >= m_cols)
        throw runtime_error("Matrix index out of range");
    return m_data[r * m_cols + c];
}

Matrix Matrix::transpose() const {
    Matrix M(m_cols, m_rows);
    for (size_t r = 0; r < m_rows; ++r)
        for (size_t c = 0; c < m_cols; ++c)
            M(c, r) = (*this)(r, c);
    return M;
}