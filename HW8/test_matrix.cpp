#include "Matrix.h"
#include <print>    

int main() {
    Matrix A(2,3);
    A[0,0]=1.0; A[0,1]=2.0; A[0,2]=3.0;
    A[1,0]=4.0; A[1,1]=5.0; A[1,2]=6.0;
   
    {
        Matrix B(2,3);
        B=A;
        B[0,0]=-1.0;

        std::println("{}",A[0,0]);
        std::println("{}",B[0,0]);       
    }
}