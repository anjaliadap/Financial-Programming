#include <iostream>
using namespace std;

long long fibonacci(long long n) {
    if (n < 0) {
        cout << "n must be non-negative";
    }

    if (n == 0) return 0;   // F0
    
    if (n == 1) return 1;   // F1
    
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {

    cout << "Enter integer number: ";
    long long n;
    cin >> n;

    long long fn = fibonacci(n);
    cout << "Fibonacci of " << n << " is " << fn << "\n";
    
    return 0;

}