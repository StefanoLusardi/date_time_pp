#include <iomanip>
#include <date/date.h>

#include "date_t.hpp"
#include "utils.hpp"

namespace dtpp
{
date_t today()
{
    auto date_point = date::floor<date::days>(std::chrono::system_clock::now());
    auto year_month_day = date::year_month_day(date_point);
    return dtpp::make_date(year_month_day);
}

date_t tomorrow()
{
    auto date_point = date::floor<date::days>(std::chrono::system_clock::now());
    date_point += date::days{ 1 };
    auto year_month_day = date::year_month_day(date_point);
    return dtpp::make_date(year_month_day);
}

bool date_t::is_valid() const
{
    date::year_month_day ymd = date::year(year)/month/day;
    return ymd.ok();
}

date_t date_t::from_string(const std::string& str, const char* fmt)
{
    std::istringstream in(str);
    date::sys_days datetime_point;
    in >> date::parse(fmt, datetime_point);
    if (in.fail())
        throw std::runtime_error("date_t::from_string - failed to parse " + str);

    auto year_month_day = date::year_month_day(datetime_point);
    return dtpp::make_date(year_month_day);
}

std::chrono::system_clock::time_point date_t::time_point() const
{
    const auto ymd = date::year(year) / month / day;
    return date::sys_days(ymd);
}


bool date_t::operator==(const date_t& d) const
{
    return year == d.year && month == d.month && day == d.day;
}

bool date_t::operator!=(const date_t& d) const
{
    return !(*this == d);
}

bool date_t::operator<(const date_t& d) const
{
    return time_point() < d.time_point();
}

bool date_t::operator>(const date_t& d) const
{
    return d.time_point() < this->time_point();
}

bool date_t::operator<=(const date_t& d) const
{
    return time_point() <= d.time_point();
}

bool date_t::operator>=(const date_t& d) const
{
    return d.time_point() <= this->time_point();
}

std::ostream& operator<<(std::ostream& os, const dtpp::date_t& d)
{
    os << std::setfill('0') << std::right << std::setw(4) << d.year 
        << '-' << std::setfill('0') << std::right << std::setw(2) << d.month
        << '-' << std::setfill('0') << std::right << std::setw(2) << d.day;
    return os;
}

}
