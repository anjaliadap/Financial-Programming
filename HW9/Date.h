
#pragma once
#include <string>
#include <iostream>

class Date {
public:
    Date() =default; 
    Date(int yyyy, int mm, int dd); // from year, month and day
    Date(std::string_view date); // from "yyyy-mm-dd" string
    // output date to stream in  "yyyy-mm-dd" format
    friend std::ostream &operator<<(std::ostream &os, Date date);    
    // input date from stream in "yyyy-mm-dd" format
    friend std::istream &operator>>(std::istream& is, Date &date);
    void split(int &year,int &month,int &day) const;
    // test ordering of dates
    auto operator<=>(const Date& rhs) const  {
        return m_days <=> rhs.m_days;
    }
    friend bool operator==(Date lhs, Date rhs) {
        return lhs.m_days == rhs.m_days;
    }

    // return new  date adding  <days> days to <lsh>
    friend Date operator+(Date lhs, double days) {
        lhs.m_days += days;
        return lhs;
    };
    // Add in-place <days> to date
    Date &operator+=(double days) {
        m_days += days;
        return *this;
    }
    // decrease date by <days> number of days
    friend Date operator-(Date lhs, double days) {
        lhs.m_days -= days;
        return lhs;
    };
    Date &operator-=(double days) {
        m_days -= days;
        return *this;
    }
    // number of dates between two dates
    friend double operator-(Date lhs, Date rhs) {
        return lhs.m_days - rhs.m_days;
    };
private:
    double m_days;
};

// return true is <year> is a leap year 
bool is_leap_year(int year);
// return the last day of month <month> in year <year>
int end_of_month_day(int year, int month);
// add <months> months to <date>
//
// this takes care of the different number of days in each month
// so that adding 1 month to 2020-01-30 gives 2020-02-29
Date add_months(Date date, int months);
