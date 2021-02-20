#include <chrono>
#include <iostream>
#include <date/date.h>

#include "datetime_t.hpp"
#include "utils.hpp"

namespace dtpp
{
std::string timestamp(const char* fmt)
{
    auto ts = std::chrono::system_clock::now();
    return date::format(fmt, std::chrono::floor<std::chrono::milliseconds>(ts));
}

datetime_t utc_now()
{
    auto datetime_point = std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now());
    auto date_point = date::floor<date::days>(datetime_point);
    auto year_month_day = date::year_month_day(date_point);
    auto time_of_day = date::make_time(datetime_point - date_point);

    return datetime_t{ dtpp::make_date(year_month_day), dtpp::make_time(time_of_day) };
}

datetime_t datetime_t::from_string(const std::string& str, const char* fmt)
{
    std::istringstream in(str);
    
    date::sys_time<std::chrono::milliseconds> datetime_point;
    in >> date::parse(fmt, datetime_point);
    if (in.fail())
        throw std::runtime_error("Failed to parse " + str);

    auto date_point = date::floor<date::days>(datetime_point);
    auto year_month_day = date::year_month_day(date_point);
    auto time_of_day = date::make_time(datetime_point - date_point);

    return datetime_t{dtpp::make_date(year_month_day), dtpp::make_time(time_of_day)};
}

datetime_t datetime_t::from_time_point(const std::chrono::system_clock::time_point& tp)
{
    auto datetime_point = tp;
    // date::sys_time<std::chrono::milliseconds> datetime_point(tp);

    auto date_point = date::floor<date::days>(datetime_point);
    auto year_month_day = date::year_month_day(date_point);
    auto time_of_day = date::make_time(datetime_point - date_point);

    return datetime_t{dtpp::make_date(year_month_day), dtpp::make_time(time_of_day)};
}

template<> 
std::chrono::system_clock::time_point 
datetime_t::time_point<std::chrono::system_clock::time_point>() const
{
    auto ymd = date::year(year())/month()/day(); 
    if (!ymd.ok())
        throw std::runtime_error("Invalid date");

    return date::sys_days(ymd) + 
        std::chrono::hours(_t.hour) + 
        std::chrono::minutes(_t.minute) + 
        std::chrono::seconds(_t.second) + 
        std::chrono::milliseconds(_t.millisecond);
}

template<> 
std::chrono::steady_clock::time_point
datetime_t::time_point<std::chrono::steady_clock::time_point>() const
{
    std::chrono::steady_clock::time_point sdy_now(std::chrono::steady_clock::now());
    std::chrono::system_clock::time_point sys_now(std::chrono::system_clock::now());
    return time_point<std::chrono::system_clock::time_point>() - sys_now + sdy_now;
}

std::ostream& operator<<(std::ostream& os, const dtpp::datetime_t& dt)
{
    os << dt.date() << 'T' << dt.time();
    return os;
}

}
