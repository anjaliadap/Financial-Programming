#pragma once
#include <string>
#include <iostream>

class Date
{
public:
    Date(int yyyy, int mm, int dd);
    Date(std::string_view date);
    // copy constructor
    Date(const Date &date) : m_days(date.m_days){};
    // number of dates between two dates
    friend double operator-(Date lhs, Date rhs)
    {
        return lhs.m_days - rhs.m_days;
    };
    // increase date by <days> number of days
    friend Date operator+(Date lhs, double days)
    {
        lhs.m_days += days;
        return lhs;
    };
    // test ordering of dates
    friend bool operator<(Date lhs, Date rhs)
    {
        return lhs.m_days < rhs.m_days;
    }
    // output date to stream
    friend std::ostream &operator<<(std::ostream &os, Date date);
    friend struct std::formatter<Date>;
private:
    double m_days;
};

std::string days_to_string(double days);
template <>
struct std::formatter<Date> : std::formatter<std::string> {
  auto format(Date date, format_context& ctx) const {
    return formatter<string>::format(
      std::format("{}", days_to_string(date.m_days)), ctx);
  }
};