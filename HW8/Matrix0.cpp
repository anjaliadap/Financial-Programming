#include "VectorDouble.h"
#include "Matrix0.h"

#include <format>
#include <exception>
#include <stdexcept>

VectorDouble Matrix::operator*(const VectorDouble &x) const {
        VectorDouble y(m_rows);
        if (x.size()!=m_cols) {
            std::string error_message=std::format("Matrix multiplication: input vector size ({} do not match matrix columns ({}).",x.size(),m_cols);
            throw std::runtime_error(error_message);
        }
        for (size_t row=0; row<m_rows;row++) {
            y[row]=0.0;
            for (size_t col=0;col<m_cols; col++) {
                y[row]+=(*this)[row,col]*x[col];
            }
        }
        return y;
    }

    Matrix Matrix::operator*(const Matrix &M) const {
        if (m_cols!=M.rows()) {
            std::string error_message=std::format("Matrix multiplication: input matrix columns ({} do not match matrix rows ({}).",m_cols,M.rows());
            throw std::runtime_error(error_message);
        }
        Matrix Z(m_rows,M.cols());
        for (size_t row=0; row<m_rows;row++) {
            for (size_t col=0;col<M.cols(); col++) {
                Z[row,col]=0.0;
                for (size_t k=0;k<m_cols; k++) {
                    Z[row,col]+=(*this)[row,k]*M[k,col];
                }
            }
        }
        return Z;
    } 

    Matrix Matrix::transpose() const {
        Matrix M(m_cols,m_rows);
        for (size_t row=0;row<m_rows;row++) {
            for (size_t col=0;col<m_cols;col++) {
                M[col,row]=(*this)[row,col];
            }
        }
        return M;
    }