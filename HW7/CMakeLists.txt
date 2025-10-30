cmake_minimum_required(VERSION 3.15)
project(HW7 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)


add_executable(HW7  HW7_Solutions.cpp date0.cpp)
add_executable(solve_portfolio solve_portfolio.cpp lu_decomposition.cpp)
