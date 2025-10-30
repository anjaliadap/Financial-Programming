// Matrix1.cpp
#include "Matrix1.h"

Matrix1 Matrix1::transpose() const {
    Matrix1 M(m_cols, m_rows);
    for (size_t r = 0; r < m_rows; ++r)
        for (size_t c = 0; c < m_cols; ++c)
            M(c, r) = (*this)(r, c);
    return M;
}