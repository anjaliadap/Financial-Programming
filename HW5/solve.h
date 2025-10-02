#pragma once

using ParameterizedFunction = double (*)(double, int size, double *params);

int solve_bisection(double x
                    , double x0
                    , double x1
                    , ParameterizedFunction function
                    , int size
                    , double * params
                    , int max_iter
                    , double tol
                    , double & result);

                