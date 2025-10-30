#include <time.h>
#include <string>
#include <sstream>
#include <math.h>
#include <iomanip>

using Date=double;

Date get_date(int yyyy, int mm, int dd) {
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

void get_yyyy_mm_dd(Date date, int &yyyy, int &mm, int &dd) {
    time_t seconds_since_epoch=24.0*60*60*(date-25569);
    const tm *time=gmtime(&seconds_since_epoch);
    yyyy=time->tm_year+1900; //years since 1900
    mm=time->tm_mon+1; // month of the year, January is 0
    dd=time->tm_mday; // day of the moth;
}

std::string date_to_string(Date date) {
    int yyyy;
    int mm;
    int dd;
    get_yyyy_mm_dd(date,yyyy,mm,dd);
    std::ostringstream ss;
    ss<<std::setfill('0')<<std::setw(4)<<yyyy<<"-"<<std::setw(2)<<mm<<"-"<<std::setw(2)<<dd;
    return ss.str(); 
}
