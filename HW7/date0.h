#pragma once
//
// date0.h  
//
// Simple API to manipulate dates in a human friendly fashion
//
// Dates are represented internally as a double counting the number 
//  of days since 1900-01-01
//
#include<string>

using Date=double; // Date is just an alias for double
// return number of days since 1900-01-01
Date get_date(int yyyy, int mm, int dd);
// given number of days since 1900-01-01 return year month and day
void get_yyyy_mm_dd(Date date, int &yyyy, int &mm, int &dd);
// given number of days since 1900-01-01 return 
//      yyyy-mm-dd formated string
std::string date_to_string(Date date);