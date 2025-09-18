#include <iostream>
using namespace std;

long long fibonacci(long long n) {
    if (n == 0) return 0;  // F0
    if (n == 1) return 1;  // F1

    long long a = 0; // F0
    long long b = 1; // F1
    for (long long i = 2; i <= n; ++i) {
        long long c = a + b; // Fi = Fi-1 + Fi-2
        a = b;               // a <- Fi-1
        b = c;               // b <- Fi
    }
    return b; // Fn
}

int main() {

    cout << "Enter integer number: ";
    long long n;
    cin >> n;

    long long fn = fibonacci(n);
    cout << "Fibonacci of " << n << " is " << fn << "\n";
    return 0;

}

/*
For n = 45, both implementations still perform decently. 
For large n, n=100, the for loop implementation is quite fast and instantaneous still, 
but the recursive implementation takes a very long time. 

The recursive version is slow because it has overlapping subproblems and recomputes them exponentially many times. 
The loop avoids that; memoization or fast-doubling fixes it while keeping recursion.
*/