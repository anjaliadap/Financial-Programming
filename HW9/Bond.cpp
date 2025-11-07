#include "Bond.h"
#include "Date.h"
#include "Discount.h"
#include "day_count.h"
#include <cmath>
#include <sstream>
using namespace std;

double bond_price(double notional
                , Date first_accrual_date
                , Date maturity
                , double coupon
                , DayCountConvention day_count
                , int frequency
                , const Discount &disc) {
    
    Date val_date=disc.valuation_date();

    if (12% frequency!=0) {
        throw invalid_argument("Frequency must be a divisor of  12");
    }

    int months=12/frequency;
    double pv=0;

    // Add principal repayment if bond not yet matured
    if (val_date<=maturity) {
        pv+=disc.discount(maturity);
    }
    
    // Coupon payments backwards from maturity
    int count=1;
    Date date=maturity;

    while (disc.valuation_date()<=date) {
        Date date0=add_months(maturity, -count*months);
        date0=max(date0,first_accrual_date);

        double dcf=day_count_fraction(date0, date,day_count);
        double df=disc.discount(date);

        pv+=dcf*coupon*df;
        date=date0;
        count++;

        if (date==first_accrual_date) {break;}
    }
    return notional*pv;
}

// Method version for a Bond object
double Bond::price(const Discount &discount) const {
    return bond_price(notional, first_accrual_date, maturity, coupon, day_count, frequency, discount);
}


std::vector<Bond> parse_bonds(std::istream &input) {
    std::vector<Bond> bonds;
    std::string line;

    while (std::getline(input, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);

        Bond b;
        ss >> b.currency
           >> b.notional
           >> b.first_accrual_date
           >> b.maturity
           >> b.coupon
           >> b.day_count
           >> b.frequency;

        if (!ss.fail()) {
            bonds.push_back(b);
        }
    }

    return bonds;
}

