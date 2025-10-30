#include "Matrix0.h"
#include <iostream>
using namespace std;

int main() {
    Matrix A(2,3);
    A[0,0]=1.0; A[0,1]=2.0; A[0,2]=3.0;
    A[1,0]=4.0; A[1,1]=5.0; A[1,2]=6.0;
   
    {
        Matrix B(2,3);
        B=A;
        B[0,0]=-1.0;

        std::cout<<A[0,0]<<endl;
        std::cout<<B[0,0]<<endl;       
    }
}