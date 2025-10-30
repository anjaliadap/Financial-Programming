#include "VectorInt.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <size>" << endl;
        return 1;
    }

    int n = atoi(argv[1]);
    VectorInt vec1(n);
    for (int i = 0; i < n; i++) vec1[i] = (i + 1) * (i + 1);
    cout << "vec1 = " << vec1 << endl;

    VectorInt vec2 = vec1;
    cout << "vec2 = " << vec2 << endl;

    for (size_t i = 0; i < vec2.size(); i++) vec2[i] = -vec2[i];
    cout << "After negating vec2:" << endl;
    cout << "vec1 = " << vec1 << endl;
    cout << "vec2 = " << vec2 << endl;

    vec1 = vec2;
    cout << "After assigning vec1 = vec2:" << endl;
    cout << "vec1 = " << vec1 << endl;

    // Problem 7
    VectorInt v1(5), v2(5), v3(5);
    for (int i = 0; i < 5; i++) {
        v1[i] = i;
        v2[i] = i * i;
    }
    v3[0]=1; v3[1]=-1; v3[2]=2; v3[3]=-2; v3[4]=3;

    VectorInt v = 3 * (v1 + 2 * v2) + (-7) * v3;
    cout << "v = " << v << endl;
}