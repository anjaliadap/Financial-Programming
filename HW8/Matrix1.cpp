#include "Matrix1.h"
#include <stdexcept>
#include <format>

VectorDouble Matrix1::operator*(const VectorDouble &x) const {
    VectorDouble y(m_rows);
    if (x.size() != m_cols) {
        std::string error_message = std::format(
            "Matrix1 multiplication: input vector size ({}) does not match matrix columns ({}).",
            x.size(), m_cols);
        throw std::runtime_error(error_message);
    }
    for (size_t row = 0; row < m_rows; row++) {
        y[row] = 0.0;
        for (size_t col = 0; col < m_cols; col++) {
            y[row] += (*this)[row, col] * x[col];
        }
    }
    return y;
}

Matrix1 Matrix1::operator*(const Matrix1 &M) const {
    if (m_cols != M.rows()) {
        std::string error_message = std::format(
            "Matrix1 multiplication: input matrix columns ({}) do not match matrix rows ({}).",
            m_cols, M.rows());
        throw std::runtime_error(error_message);
    }
    Matrix1 Z(m_rows, M.cols());
    for (size_t row = 0; row < m_rows; row++) {
        for (size_t col = 0; col < M.cols(); col++) {
            Z[row, col] = 0.0;
            for (size_t k = 0; k < m_cols; k++) {
                Z[row, col] += (*this)[row, k] * M[k, col];
            }
        }
    }
    return Z;
}

Matrix1 Matrix1::transpose() const {
    Matrix1 M(m_cols, m_rows);
    for (size_t row = 0; row < m_rows; row++) {
        for (size_t col = 0; col < m_cols; col++) {
            M[col, row] = (*this)[row, col];
        }
    }
    return M;
}
