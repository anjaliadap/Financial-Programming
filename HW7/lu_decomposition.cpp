
#include "lu_decomposition.h"
#include <cmath>

void matrix_multiplication(const Matrix &A, const Matrix &B, Matrix &C) {
    size_t D=A.rows();
    for (size_t i = 0; i < D; i++) {
        for (size_t j = 0; j < D; j++) {
            C[i,j] = 0;
            for (size_t k = 0; k < D; k++) {
                C[i,j] += A[i,k] * B[k,j];
            }
        }
    }
}

void matrix_vector_multiplication(const Matrix &A, double *v, double *result) {
    size_t D=A.rows();
    for (int i=0;i<D;i++) {
        result[i]=0;
        for (int j=0;j<D;j++) {
            result[i]+=A[i,j]*v[j];
        }
    }
}

void solve_linear_system(Matrix &A, double *b) {
   
    size_t D=A.rows();
    for (size_t col=0;col<D;col++) {
        // Pivoting
        size_t pivot_row=col;
        double pivot_value=A[pivot_row,col];
        for (size_t row=col+1;row<D;row++) {
            if (std::fabs(A[row,col])>std::fabs(pivot_value)) {
                pivot_row=row;
                pivot_value=A[row,col];
            }
        }
        if (pivot_row!=col) {
            // Swap rows
            for (size_t j=col;j<D;j++) {
                double temp=A[col,j];
                A[col,j]=A[pivot_row,j];
                A[pivot_row,j]=temp;
            }
            double temp=b[col];
            b[col]=b[pivot_row];
            b[pivot_row]=temp;
        }
        // Elimination
        for (size_t row=col+1;row<D;row++) {
            double factor=A[row,col]/A[col,col];
            b[row]-=factor*b[col];
            for (size_t j=col;j<D;j++) {
                A[row,j]-=factor*A[col,j];
            }
        }
    }
    // Back substitution
    for (size_t col=D;col-->0;) {
        b[col]=b[col]/A[col,col];
        if (col==0) break;
        for (size_t row=0;row<col;row++) {
            b[row]-=A[row,col]*b[col];
        }
    }
}

void lu_decomposition(const Matrix &A, Matrix &L,  Matrix &U) {
    size_t D=A.rows();
    for (size_t i = 0; i < D; i++) {
        for (size_t j = 0; j < D; j++) {
            if (j < i)
                L[j,i] = 0;
            else {
                L[j,i] = A[j,i];
                for (size_t k = 0; k < i; k++) {
                    L[j,i] -= L[j,k] * U[k,i];
                }
            }
        }
        for (size_t j = 0; j < D; j++) {
            if (j < i)
                U[i,j] = 0;
            else if (j == i)
                U[i,j] = 1;
            else {
                U[i,j] = A[i,j] / L[i,i];
                for (size_t k = 0; k < i; k++) {
                    U[i,j] -= (L[i,k] * U[k,j]) / L[i,i];
                }
            }
        }
    }
}


void solve_forward(const Matrix &L, double *b) {
    size_t D=L.rows();
    for (size_t col=0;col<D;col++) {
        double pivot=L[col,col];
        b[col]=b[col]/pivot;
        for (size_t row=col+1;row<D;row++) {
            b[row]-=L[row,col]*b[col];
        }
    }
}

void solve_backward(const Matrix &U, double *b) {
    size_t D=U.rows();
    for (size_t col=D;col-->0;) {
        double pivot=U[col,col];
        b[col]=b[col]/pivot;
        if (col==0) break;
        for (size_t row=col;row-->0;) {
            b[row]-=U[row,col]*b[col];
        }
    }
}

void solve_lu(const Matrix &L, const Matrix &U, double *b) {
    solve_forward(L,b);
    solve_backward(U,b);
}



