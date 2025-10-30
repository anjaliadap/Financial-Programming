// test_matrix1.cpp
#include "Matrix1.h"
#include <iostream>
using namespace std;

int main() {
    Matrix1 A(2,3);
    A(0,0)=1.0; A(0,1)=2.0; A(0,2)=3.0;
    A(1,0)=4.0; A(1,1)=5.0; A(1,2)=6.0;

    {
        Matrix1 B(2,3);
        B = A;
        B(0,0) = -1.0;

        cout << "A(0,0) = " << A(0,0) << endl;
        cout << "B(0,0) = " << B(0,0) << endl;
    }

    cout << "Creating transpose of A:" << endl;
    Matrix1 T = A.transpose();

    for (size_t r = 0; r < T.rows(); ++r) {
        for (size_t c = 0; c < T.cols(); ++c)
            cout << T(r,c) << " ";
        cout << endl;
    }
}