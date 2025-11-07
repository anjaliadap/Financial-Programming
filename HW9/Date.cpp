#define _CRT_SECURE_NO_WARNINGS // needed by Microsoft compiler
#include <time.h>
#include <string>
#include <sstream>
#include <math.h>
#include <iomanip>
#include <charconv>


#include "Date.h"

using namespace std;

static double get_date(int yyyy, int mm, int dd) {
    tm time{};
    time.tm_year=yyyy-1900; //years since 1900
    time.tm_mon=mm-1; // month of the year, January is 0
    time.tm_mday=dd; // day of the moth;
    time_t seconds_since_1970_01_01=mktime(&time);
    // Detect if  date is out of range (say 2022-02-31) 
    // the call to mktime will update the fields to the interpreted value ie. 2022-03-03)
    if ((time.tm_year!=yyyy-1900)||
        (time.tm_mon!=mm-1)  ||
        (time.tm_mday!=dd)) 
        {
            std::ostringstream ss;
            ss<<"Date '"<<yyyy<<"-"<<mm<<"-"<<dd<<"' is a invalid date";
            throw std::runtime_error(ss.str());
        }


    double days_since_1900_01_01=std::floor(seconds_since_1970_01_01/(24.0*60*60)+25569); // in days;
    return days_since_1900_01_01;
}

static void get_yyyy_mm_dd(double date, int &yyyy, int &mm, int &dd) {
    time_t seconds_since_epoch=std::lround(24.0*60*60*(date-25569));
    const tm *time=gmtime(&seconds_since_epoch);
    yyyy=time->tm_year+1900; //years since 1900
    mm=time->tm_mon+1; // month of the year, January is 0
    dd=time->tm_mday; // day of the moth;
}

static std::string days_to_string(double days) {
    int yyyy;
    int mm;
    int dd;
    get_yyyy_mm_dd(days,yyyy,mm,dd);
    std::ostringstream ss;
    ss<<std::setfill('0')<<std::setw(4)<<yyyy<<"-"<<std::setw(2)<<mm<<"-"<<std::setw(2)<<dd;
    return ss.str(); 
}

Date::Date(int yyyy, int mm, int dd): m_days(get_date(yyyy,mm,dd)) {};

// yyyy-mm-dd
Date::Date(std::string_view view) {
    if ( (view.size()!=10) || (view[4]!='-') || (view[7]!='-')) {
        ostringstream ss;
        ss<<"Bad date format '"<<view<<"', expected yyyy-mm-dd";
        throw std::runtime_error(ss.str());
    } 
    int yyyy;
    int mm;
    int dd;
    auto res=from_chars(view.data(),view.data()+4,yyyy);
    if (res.ec!=errc()) {
         ostringstream ss;
        ss<<"Bad  year '"<<view.substr(0,4)<<"' for date '"<<view<<"'";
        throw std::runtime_error(ss.str());
    }
    res=from_chars(view.data()+5,view.data()+7,mm);
    if (res.ec!=errc()) {
        ostringstream ss;
        ss<<"Bad  month '"<<view.substr(5,7)<<"' for date '"<<view<<"'";
        throw std::runtime_error(ss.str());
    }
    res=from_chars(view.data()+8,view.data()+view.size(), dd);
    if (res.ec!=errc()) {
        ostringstream ss;
        ss<<"Bad  day '"<<view.substr(8,view.size())<<"' for date '"<<view<<"'";
        throw std::runtime_error(ss.str());
    }
    *this=Date(yyyy,mm,dd);

}

void Date::split(int &year,int &month,int &day) const {
    get_yyyy_mm_dd(m_days,year,month,day);
}

std::ostream &operator<<(std::ostream& os, Date date ) {
    os<<days_to_string(date.m_days);
    return os;
}

std::istream &operator>>(std::istream& is, Date &date ) {
    string date_str;
    
        is>>date_str; // read date string
   
    try {
        date=Date(date_str); // parse string
    }
    catch (std::exception &error) {
        // set the stream to the error state
        // to notify caller
       //std::cout.setstate(std::ios::failbit);
       is.setstate(std::ios::failbit);
    }
    return is;
}


// return true if year is a leap year
bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}


// return last day of month for given year and month
int end_of_month_day(int year, int month) {

    if (month == 2)//February
        if (is_leap_year(year))
            return 29;
        else
            return 28;
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else
        return 31;
}


Date add_months(Date date, int months) {
    int year, month, day;
    date.split(year, month, day);
    month += months;
    while (month > 12) {
        month -= 12;
        year++;
    }
    while (month < 1) {
        month += 12;
        year--;
    }
    int days_in_month = end_of_month_day(year, month);
    if (day > days_in_month) {
        day = days_in_month;
    }
    return Date(year, month, day);
}