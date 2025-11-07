#include "Date.h"
#include "day_count.h"

//
// Implementations of Date Count Fraction methods
// See https://quant.opengamma.io/Interest-Rate-Instruments-and-Market-Conventions.pdf
// for a nice, user friendly explanation of day count conventions.
//
// And https://www.rbccm.com/assets/rbccm/docs/legal/doddfrank/Documents/ISDALibrary/2006%20ISDA%20Definitions.pdf
// for the actual, authoritative source of the definitions.
//


 

static double one_one([[maybe_unused]] Date date1,
                      [[maybe_unused]] Date date2) {
    // This is definition 4.16(a) in 2006 ISDA Definitions.
    return 1.0;
}

static double thirty_E_360(Date date1, Date date2) {
    // This is definition 4.16(g) in 2006 ISDA Definitions.
    //If D1 is 31, then change D1 to 30.
    //If D2 is 31, then change D2 to 30.
    int y1, m1, d1;
    int y2, m2, d2;
    date1.split(y1, m1, d1);
    date2.split(y2, m2, d2);
    if (d1 == 31) 
        d1 = 30;
    if (d2 == 31) 
        d2 = 30;
    double N=360 * (y2 - y1) + 30 * (m2 - m1) + (d2 - d1);
    double D=360;
    return N/D;
}

static double thirty_360(Date date1, Date date2) {
    // This is definition 4.16(f) in 2006 ISDA Definitions.
    //If D1 is 31, then change D1 to 30.
    //If D2 is 31 and D1 is 30 or 31, then change D2 to 30
    int y1, m1, d1;
    int y2, m2, d2;
    date1.split(y1, m1, d1);
    date2.split(y2, m2, d2);
    if (d1 == 31) 
        d1 = 30;
    if ((d2 == 31) && (d1 == 30 || d1 == 31)) 
        d2 = 30;
    double N=360 * (y2 - y1) + 30 * (m2 - m1) + (d2 - d1);
    double D=360;
    return N/D;
}

// WARNING: This has a special provision if date2 is the Termination date 
// that we are ignoring here.
static double thirty_E_360_ISDA(Date date1, Date date2) {
    // This is definition 4.16(h) in 2006 ISDA Definitions.
    // If D1 is the last day of the month, then change D1 to 30.
    // If D2 is the last day of February but not the termination date or D2 is 31, then change D2 to 30.
    int y1, m1, d1;
    int y2, m2, d2;
    date1.split(y1, m1, d1);
    date2.split(y2, m2, d2);
    if (d1 == 31) 
        d1 = 30;
    if ( ((m2==2) && (d2 == end_of_month_day(y2, m2))) || (d2 == 31))
        d2 = 30;
    double N=360 * (y2 - y1) + 30 * (m2 - m1) + (d2 - d1);
    double D=360;
    return N/D;
}

static double thirty_E_plus_360(Date date1, Date date2) {
   // The date adjustment rules are the following:
   // If D1 is 31, then change D1 to 30.
   // If D2 is 31, then change D2 to 1 and M2 to M2+1.
    int y1, m1, d1;
    int y2, m2, d2;
    date1.split(y1, m1, d1);
    date2.split(y2, m2, d2);
    if (d1 == 31) 
        d1 = 30;
    if (d2 == 31) {
        d2 = 1;
        m2++;
    }
    double N=360 * (y2 - y1) + 30 * (m2 - m1) + (d2 - d1);
    double D=360;
    return N/D;
}

static double actual_360(Date date1, Date date2) {
    // This is definition 4.16(e) in 2006 ISDA Definitions.
    // The day count fraction is calculated as the actual number of days between the two dates divided by 360.
    return (date2 - date1) / 360;
}

static double actual_365_fixed(Date date1, Date date2) {
    // This is definition 4.16(d) in 2006 ISDA Definitions.
    // The day count fraction is calculated as the actual number of days between the two dates divided by 365.
    return (date2 - date1) / 365;
}

//  the following calculation assumes date1 and date2 are less than 4 years apart
// so we do not worry about multiple leap years
//
static double actual_365_A(Date date1, Date date2) {
    //The accrual factor is
    //   (d2 − d1)/D
    // where the Denominator D is 366 if 29 February is 
    // between d1 (exclusive) to d2 (inclusive) and 365 otherwise.
    // The convention is also called ACT/365 Actual.
    int y1, m1, d1;
    int y2, m2, d2;
    date1.split(y1, m1, d1);
    date2.split(y2, m2, d2);
    double D;
    if (is_leap_year(y1)) {
        if ((m1>2) || (m1==2 && d1==29)) { // d1 pass the leap date
            D=365;
        }
        else if ((y2>y1) ||  (m2>2) || ((d2==2) &&  (d2==29)) ) {// d1 before, d2 after leap date
                D = 366;
        }
        else {
            D = 365;
        }
    }
    else {// y1 is not a leap year
        if  (is_leap_year(y2) && ((m2>2) || (m2==2 && d2==29))) { // d2 pass the leap date
                D=366;
        }
        else {
            D = 365;
        }
    }
    return (date2 - date1) / D;
}

static double actual_actual_ISDA(Date date1, Date date2) {
    //This is definition 4.16(b) in 2006 ISDA Definitions. The accrual factor is
   // (Days in a non-leap year)/365 + (Days in a leap year)/366
   //To compute the number of days, the period first day is included and the last day is excluded
    int y1, m1, d1;
    int y2, m2, d2;
    date1.split(y1, m1, d1);
    date2.split(y2, m2, d2);
    double D;
    if (y1==y2) {
        if (is_leap_year(y1)) {
            D=366;
        }
        else {
           D= 365;
        }
        return (date2 - date1) / D;
    }
    double D1;
    double D2;
    Date eoy=Date(y1,12,31);
    if (is_leap_year(y1)) {
        D1=366;
        D2=365;
    }
    else if(is_leap_year(y2)) {
        D1 = 365;
        D2=366;
    }
    else {
        D1=365;
        D2=365;
    }
    return (eoy-date1)/D1 + (date2-eoy)/D2;
}

double day_count_fraction(Date date1, Date date2, DayCountConvention convention) {
    switch (convention) {
    case DayCountConvention::ONE_ONE:
        return one_one(date1, date2);
    case DayCountConvention::THIRTY_E_360:
        return thirty_E_360(date1, date2);
    case DayCountConvention::THIRTY_360:
        return thirty_360(date1, date2);
    case DayCountConvention::THIRTY_E_360_ISDA:
        return thirty_E_360_ISDA(date1, date2);
    case DayCountConvention::THIRTY_E_PLUS_360:
        return thirty_E_plus_360(date1, date2);
    case DayCountConvention::ACT_360:
        return actual_360(date1, date2);
    case DayCountConvention::ACT_365_FIXED:
        return actual_365_fixed(date1, date2); 
    case DayCountConvention::ACT_365_A:
        return actual_365_A(date1, date2);
    case DayCountConvention::ACT_ACT_ISDA:
        return actual_actual_ISDA(date1, date2);
    default:
        throw std::runtime_error("Unknown day count convention");
    }
}

std::string day_count_convention_to_string(DayCountConvention convention) {
    switch (convention) {
    case DayCountConvention::ONE_ONE:
        return "1/1";
    case DayCountConvention::THIRTY_360:
        return "30/360";
    case DayCountConvention::THIRTY_E_360:
        return "30E/360";
    case DayCountConvention::THIRTY_E_360_ISDA:
        return "30E/360_ISDA";
    case DayCountConvention::THIRTY_E_PLUS_360:
        return "30E+/360";
    case DayCountConvention::ACT_360:
        return "ACT/360";
    case DayCountConvention::ACT_365_FIXED:
        return "ACT/365_Fixed";
    case DayCountConvention::ACT_365_A:
        return "ACT/365A";
    case DayCountConvention::ACT_ACT_ISDA:
        return "ACT/ACT_ISDA";
    }
    throw std::invalid_argument("Unknown day count convention "+std::to_string(static_cast<int>(convention)));
}

DayCountConvention string_to_day_count_convention(std::string_view view) {
    if (view == "1/1") {
        return DayCountConvention::ONE_ONE;
    }
    if (view == "30/360") {
        return DayCountConvention::THIRTY_360;
    }
    if (view == "30E/360") {
        return DayCountConvention::THIRTY_E_360;
    }
    if (view == "30E/360_ISDA") {
        return DayCountConvention::THIRTY_E_360_ISDA;
    }
    if (view == "30E+/360") {
        return DayCountConvention::THIRTY_E_PLUS_360;
    }
    if (view == "ACT/360") {
        return DayCountConvention::ACT_360;
    }
    if (view == "ACT/365_Fixed") {
        return DayCountConvention::ACT_365_FIXED;
    }
    if (view == "ACT/365A") {
        return DayCountConvention::ACT_365_A;
    }
    if (view == "ACT/ACT_ISDA") {
        return DayCountConvention::ACT_ACT_ISDA;
    }
    throw std::invalid_argument("Unknown day count convention");
};

std::ostream &operator<<(std::ostream &os, DayCountConvention convention) {
    os << day_count_convention_to_string(convention);
    return os;
}   

std::istream &operator>>(std::istream &is, DayCountConvention &convention) {
    std::string view;
    is >> view;
    convention = string_to_day_count_convention(view);
    return is;
}