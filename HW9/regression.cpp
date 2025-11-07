#include <Eigen/Dense>
#include <Eigen/Cholesky>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include <stdexcept>
#include <format>
#include <print>
using namespace std;
using namespace Eigen;

void parse_implied_vols(const std::string &filename, 
                        std::vector<double> &strikes, 
                        std::vector<double> &vols)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file");
    }

    std::string header;
    std::getline(file, header); // Skip header line
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream line_stream(line);
        double K, sigma;
        std::string cell;
        std::getline(line_stream, cell, ',');
        K=std::stod(cell);
        std::getline(line_stream, cell, ',');
        sigma=std::stod(cell);
        strikes.push_back(K);
        vols.push_back(sigma);
    }
}


VectorXd poly_fit(const std::vector<double> &x,
                  const std::vector<double> &y,
                  int degree)
{
    int n = x.size();
    MatrixXd X(n, degree + 1);
    VectorXd Y(n);

    for (int i = 0; i < n; ++i)
    {
        Y(i) = y[i];
        double val = 1.0;
        for (int j = 0; j <= degree; ++j)
        {
            X(i, j) = val;
            val *= x[i];
        }
    }

    // Solve (X'X) * beta = X'y
    return (X.transpose() * X).ldlt().solve(X.transpose() * Y);
}

double poly_eval(const VectorXd &coeffs, double x)
{
    double result = 0.0;
    double term = 1.0;
    for (int i = 0; i < coeffs.size(); ++i)
    {
        result += coeffs[i] * term;
        term *= x;
    }
    return result;
}

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <implied_vols.csv>\n";
        return 1;
    }

    try
    {
        vector<double> strikes, vols;
        parse_implied_vols(argv[1], strikes, vols);

        int degree = 3; // cubic fit
        VectorXd coeffs = poly_fit(strikes, vols, degree);

        // --- CSV Header ---
        cout << "K,vol,vol_fit\n";

        // --- Print results for all strikes ---
        for (size_t i = 0; i < strikes.size(); ++i)
        {
            double fitted = poly_eval(coeffs, strikes[i]);
            cout << fixed << setprecision(0) << strikes[i] << ","
                 << setprecision(6) << vols[i] << ","
                 << fitted << "\n";
        }
    }
    catch (const std::exception &ex)
    {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }

    return 0;
}