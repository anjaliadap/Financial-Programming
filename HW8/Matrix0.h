#pragma once
#include "VectorDouble.h"

#include <iostream>
class Matrix {
    private:
        size_t m_rows;
        size_t m_cols;
        double *m_data;
    public:
    Matrix(size_t rows, size_t cols):
        m_rows{rows}, 
        m_cols{cols},
        m_data(nullptr)
        {
            //std::cerr<<"Calling Matrix constructor\n";
            m_data=new double[m_rows*m_cols];
        }
    ~Matrix() {
        //std::cerr<<"Calling Matrix destructor\n";
        delete [] m_data;
    }
    size_t rows() const { return m_rows;  }
    size_t cols() const { return m_cols; }
    inline double operator[](size_t row, size_t col) const {
        return m_data[m_cols*row+col];
    }
    inline double & operator[](size_t row, size_t col) {
           return m_data[m_cols*row+col];
    }
    Matrix transpose() const;
    VectorDouble  operator*(const VectorDouble &x) const ;
    Matrix operator*(const Matrix &x) const;   
};