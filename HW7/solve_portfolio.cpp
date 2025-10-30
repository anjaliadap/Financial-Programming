
#include <print>
#include <iostream>
using namespace std;
#include "lu_decomposition.h"

void printMatrix(const Matrix &A ) {
    size_t D=A.rows();
     for(int i=0;i<D;i++) {
        std::cout<<"\t";
        for(int j=0;j<D;j++) {
           print("\t{:0.4}",A[i,j]);
        }
        println();
    }
}

void printVector(const double *v, size_t D) {
    for (size_t i=0;i<D;i++) {
        println("\t{:0.4}",v[i]);
    }
}

int main() {
    const size_t D = 3;

    // allocate raw storage for each matrix (3×3 = 9 doubles)
    double Adata[D*D];
    double Ldata[D*D];
    double Udata[D*D];

    // construct matrices using the 3-argument constructor
    Matrix A(D, D, Adata);
    Matrix L(D, D, Ldata);
    Matrix U(D, D, Udata);

    // Option risk exposures matrix
    A[0,0] = 50'000'000;  A[0,1] = 20'000'000;  A[0,2] = 20'000'000;
    A[1,0] = -25'000;     A[1,1] = -15'000;     A[1,2] = -20'000;
    A[2,0] = 700'000;     A[2,1] = 150'000;     A[2,2] = 350'000;

    // Portfolio risk vector
    double b[D] = {100'000'000, -50'000, 1'000'000};

    // Decompose and solve
    lu_decomposition(A, L, U);
    solve_lu(L, U, b);  // b becomes the solution x

    println("Option notionals (weights):");
    printVector(b, D);

    return 0;
}