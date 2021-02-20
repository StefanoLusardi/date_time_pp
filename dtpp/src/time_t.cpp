#include <iomanip>
#include <date/date.h>

#include "time_t.hpp"
#include "utils.hpp"

namespace dtpp
{
bool time_t::is_valid() const
{
    return hour >= 0 && hour <= 24 &&
        minute >= 0 && minute <= 60 &&
        second >= 0 && second <= 60 &&
        millisecond >= 0 && millisecond <= 999;
}

time_t time_t::from_string(const std::string& str, const char* fmt)
{
    std::istringstream in(str);
    std::chrono::milliseconds datetime_point;
    in >> date::parse(fmt, datetime_point);
    if (in.fail())
        throw std::runtime_error("Failed to parse " + str);

    auto time_of_day = date::make_time(datetime_point);
    return dtpp::make_time(time_of_day);
}

std::chrono::hours time_t::to_hours() const
{
    return std::chrono::duration_cast<std::chrono::hours>(to_millis());
}

std::chrono::minutes time_t::to_minutes() const
{
    return std::chrono::duration_cast<std::chrono::minutes>(to_millis());
}

std::chrono::seconds time_t::to_seconds() const
{
    return std::chrono::duration_cast<std::chrono::seconds>(to_millis());
}

std::chrono::milliseconds time_t::to_millis() const
{
    return std::chrono::hours(hour) + std::chrono::minutes(minute) + std::chrono::seconds(second) + std::chrono::milliseconds(millisecond);
}

bool time_t::operator==(const time_t& t) const
{
    return hour == t.hour && minute == t.minute && second == t.second && millisecond == t.millisecond;
}

bool time_t::operator!=(const time_t& t) const
{
    return !(*this == t);
}

bool time_t::operator<(const time_t& t) const
{
    return to_millis() < t.to_millis();
}

bool time_t::operator>(const time_t& t) const
{
    return t.to_millis() < this->to_millis();
}

bool time_t::operator<=(const time_t& t) const
{
    return to_millis() <= t.to_millis();
}

bool time_t::operator>=(const time_t& t) const
{
    return t.to_millis() <= this->to_millis();
}

std::ostream& operator<<(std::ostream& os, const dtpp::time_t& t)
{
    os << std::setfill('0') << std::right << std::setw(2) << t.hour 
        <<':' << std::setfill('0') << std::right << std::setw(2) << t.minute
        <<':' << std::setfill('0') << std::right << std::setw(2) << t.second
        <<'.' << std::setfill('0') << std::right << std::setw(3) << t.millisecond;
    return os;
}

}