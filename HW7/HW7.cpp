#include <string>
#include <iostream>
#include <iomanip>
#include <math.h>
#include "date0.h"

using namespace std;

//
// Problem 1
//
// Implement the function bond_price 
// using the formula given in HW7.pdf
//
double bond_price(double notional
                , Date maturity
                , double coupon
                , int frequency
                , Date valuation_date
                , double rate){

    // Calculate number of days between maturity and valuation
    double days_to_maturity = maturity - valuation_date;

    // Number of coupon periods until maturity
    int k = int(days_to_maturity * frequency / 365.0);

    double price = 0.0;

    // Loop backward from maturity to valuation_date
    for (int i = 0; i <= k; ++i) {
        // each coupon date is maturity - (365/frequency)*i
        Date di = maturity - int(365.0 / frequency * i);

        // time in years from valuation_date to this payment
        double ti = (di - valuation_date) / 365.0;

        // discount factor e^{-r * t}
        double df = exp(-rate * ti);

        // Add coupon payments (except principal term handled separately)
        price += (coupon / frequency) * df;
    }

    // Add the discounted notional repayment at maturity
    double t0 = (maturity - valuation_date) / 365.0;
    double df0 = exp(-rate * t0);

    price += df0;

    // Multiply by notional
    return notional * price;

}; 

//
// Problem 2
//
//  Add a new public const member function 
//      Date valuation_date()
//  to Discount returning the valuation date of the discount object
// 
class Discount {
    public:
        // This is a constructor 
        Discount (Date valuation_date, double rate): 
            m_valuation_date(valuation_date),
            m_rate(rate) {
                if (m_valuation_date<0) 
                { 
                    throw std::runtime_error( // raise an exception
                    "Was not expecting a date before 1900"); 
                }
            }

        Date valuation_date() const{
            return m_valuation_date;
        };

        // This is a destructor: indicated by "~". 
        // It cleans up when an object goes out of scope.  
         ~Discount() {};

        double discount(Date expiry) const {
            double T=get_T(expiry); // expiry in years from valuation date
            return exp(-T*m_rate); }  

    private: // this is not accessible from outside the class
        Date m_valuation_date;
        double m_rate;
        double get_T(Date expiry) const { 
            return  (expiry-m_valuation_date)/365.0; 
        }
};

//
// Problem 3
//
// Implement a struct Bond0
//
// It must contains the following member variables 
//      double notional
//      string currency
//      Date maturity
//      double coupon
//      int frequency.
// and the member function
//      double price(Date valuation_date, double rate)
// returning the price of the bond
//
struct Bond0 {
    string currency;
    double notional;
    Date maturity;
    double coupon;
    int frequency;

    double price(Date valuation_date, double rate) const {
        return bond_price(notional, maturity, coupon, frequency, valuation_date, rate);
    }
};

//
// Problem 4
//
// Implement  an overloaded version of the function bond_price()
// taking a Discount object instead of a valuation_date and rate arguments
//
double bond_price(double notional,
                  Date maturity,
                  double coupon,
                  int frequency,
                  const Discount &disc)
{
    double days_to_maturity = maturity - disc.valuation_date();
    int k = int(days_to_maturity * frequency / 365.0);
    double price = 0.0;

    // Loop backward from maturity to valuation date
    for (int i = 0; i <= k; ++i) {
        Date di = maturity - int(365.0 / frequency * i);
        // use Discount::discount() instead of exp(-r*t)
        double df = disc.discount(di);
        price += (coupon / frequency) * df;
    }

    // principal repayment at maturity
    price += disc.discount(maturity);

    return notional * price;
}

//
// Problem 5
//
// Implement a struct Bond
//
// It must contains member variables 
// double notional, string currency, Date maturity, double coupon and int frequency.
// and the member function 
//      double price() 
// that takes as input a Discount object instead of valuation_date and rate
//
struct Bond {
    string currency;
    double notional;
    Date maturity;
    double coupon;
    int frequency;

    double price(const Discount &disc) const {
        return bond_price(notional, maturity, coupon, frequency, disc);
    }
};

//
// Problem 6
//
// Write a for loop pricing the bonds in array bonds[]
// 
// with valuation date 2022-10-15 and with interest rate 
//       0.04 if the bond currency is USD 
//       0.01 if the bond currency is EUR
//
// Output a table of comma separated values
// with the columns:
//      notional,currency,maturity,coupon,price
//       
// for each one of the bonds in the array bonds[]
// make sure to price a heading row with the name of each column 
//
int main() {
    Bond bonds[] = {
        {"USD", 1e6,  get_date(2032,10,15), 0.06, 2},
        {"USD", 10e6,  get_date(2042,10,15), 0.06, 2},
        {"USD", 2e6,  get_date(2032,10,15), 0.02, 2},
        {"EUR", 1e6,  get_date(2032,10,15), 0.06, 1},
        {"EUR", 3e6,  get_date(2032,10,15), 0.06, 1},
        {"EUR", 5e6,  get_date(2032,10,15), 0.02, 1},
    };

    Date val_date = get_date(2022,10,15);

    // Discount curves for each currency
    Discount usd_disc(val_date, 0.04);
    Discount eur_disc(val_date, 0.01);

    // CSV header
    cout << "notional, currency, maturity, coupon, price" << endl;

    int num_bonds = sizeof(bonds) / sizeof(bonds[0]);

    for (int i = 0; i < num_bonds; ++i) {
        const Bond &b = bonds[i];
        double price = 0.0;

        if (b.currency == "USD") {
            price = b.price(usd_disc);
        } else if (b.currency == "EUR") {
            price = b.price(eur_disc);
        }

        cout << fixed << setprecision(2)
             << b.notional << ", "
             << b.currency << ", "
             << date_to_string(b.maturity) << ", "
             << b.coupon << ", "
             << price << endl;
    }

    return 0;
}
