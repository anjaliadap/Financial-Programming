#include <cmath>
#include <algorithm>
#include <iostream>
#include <print>
using namespace std;

int main() {
    double x=3.0;
   
    // Problem 1.1
    double y_1;
    y_1 = 2 + (3*x) + (4*pow(x,2));
    println("y_1 = {}", y_1, "\n");
    
    // Problem 1.2
    double y_2;
    y_2 = (x/(1+x)) * exp(-2*x);
    println("y_2 = {}", y_2, "\n");

    // Problem 2.1
    double a_0=1; 
    double a_1=-2;
    double a_2=1;
    double a_3=1;
    double y_3; 
    y_3 = a_0 + (a_1*x) + (a_2*pow(x, 2)) + (a_3*pow(x, 3));
    println("y_3 = {}", y_3, "\n");

    // Problem 2.2
    double y_4;
    y_4 = (a_0 + (a_1*x)) / (a_2 + (a_3*x));
    println("y_4 = {}", y_4, "\n");


    // Problem 3.1
    double K=100;
    double S=110;
    double call;

    if (S > K) { call = S - K; }
    else { call = 0; }
    println("call = {}", call, "\n");

    
    // Problem 3.2
    double put;
    if (S < K) { put = K - S; }
    else { put = 0; }
    println("put = {}", put, "\n");
    
    // Problem 3.3
    bool is_call=true;

    if (is_call && (S > K)) {println("option = {}", (S - K), "\n");}
    else if (!is_call && (S < K)) {println("option = {}", (K - S), "\n");}
    else { println("option = {}", 0, "\n");}
    
    // Problem 3.4
    double call2;
    double put2;

    call2 = max((S - K), 0.0);
    put2 = max((K - S), 0.0);

    println("call2 = {}", call2, "\n");
    println("put2 = {},", put2, "\n");

    // Problem 4.1
    double T=10;
    double r=0.04;
    double c=0.05;
    double bond_price = 0;

    int i = 0;
    while (i < T) {
        bond_price += c * exp(-r * (i+1));
        i++;
    }
    bond_price += exp(-r * T);
    println("bond_price = {}", bond_price, "\n");

    // Problem 4.2
    double bond_price2 = 0; 
    int j; 
    for(j = 0; j < T; j++) {
        bond_price2 += c * exp(-r * (j+1));
    }
    bond_price2 += exp(-r * T);
    println("bond_price2 = {}", bond_price2);
}