#include <iostream>
#include <string> 
#include <cmath>  

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: ./statistics <count>\n";
        return 1;
    }
    int count = std::stoi(argv[1]);

    double* data = new double[count];
    double sum = 0.0;

    for (int i = 0; i < count; ++i) {
        std::cout << "Enter number " << (i + 1) << ": ";
        double x;
        std::cin >> x;
        if (x < 0.0) {
            std::cerr << "Error: negative values are not allowed.\n";
            delete[] data; 
            return 1;
        }
        data[i] = x;
        sum += x;
    }

    double mean = sum / count;
    std::cout << "mean = " << mean << "\n";

    double ssq = 0.0;
    for (int i = 0; i < count; ++i) {
        double d = data[i] - mean;
        ssq += d * d;
    }
    double stddev = std::sqrt(ssq / (count - 1));
    std::cout << "std = " << stddev << "\n";

    delete[] data;
    return 0;
}