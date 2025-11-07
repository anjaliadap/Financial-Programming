#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Discount.h"
#include "day_count.h"
#include "Date.h"

struct Bond {
    std::string currency;
    double notional;
    Date first_accrual_date;
    Date maturity;
    double coupon;
    DayCountConvention day_count;
    int frequency;
    double price(const Discount &discount) const;
};

// Function to read multiple bonds from a stream (like bonds.txt)
std::vector<Bond> parse_bonds(std::istream &input);

// Bond pricing helper
double bond_price(double notional,
                  Date first_accrual_date,
                  Date maturity,
                  double coupon,
                  DayCountConvention day_count,
                  int frequency,
                  const Discount &disc);
