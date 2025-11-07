#pragma once
#include "Date.h"
# include <string>
# include <string_view>
# include <iostream>
# include <stdexcept>

//
// Implementations of Date Count Fraction methods
// See https://quant.opengamma.io/Interest-Rate-Instruments-and-Market-Conventions.pdf
// for a nice, user friendly explanation of day count conventions.
//
// And https://www.rbccm.com/assets/rbccm/docs/legal/doddfrank/Documents/ISDALibrary/2006%20ISDA%20Definitions.pdf
// for the actual, authoritative source of the definitions.
//

enum class DayCountConvention {
    ONE_ONE,
    THIRTY_360,
    THIRTY_E_360,
    THIRTY_E_360_ISDA,
    THIRTY_E_PLUS_360,
    ACT_360,
    ACT_365_FIXED,
    ACT_365_A,
    ACT_ACT_ISDA
};


//
// Calculate the day count fraction between two dates
//
// date1: the start date (inclusive)
// date2: the end date (exclusive)
// convention: the day count convention to use
double day_count_fraction(Date date1, Date date2, DayCountConvention convention);

std::string day_count_convention_to_string(DayCountConvention convention);
DayCountConvention string_to_day_count_convention(std::string_view view);
std::ostream &operator<<(std::ostream &os, DayCountConvention convention);
std::istream &operator>>(std::istream &is, DayCountConvention &convention);