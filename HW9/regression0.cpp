#include <Eigen/Dense>
#include <Eigen/Cholesky>
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


int main(int argc, const char *argv[])
{
    

    
}