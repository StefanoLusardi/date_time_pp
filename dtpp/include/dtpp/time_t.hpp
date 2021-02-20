#pragma once

#include "api.hpp"

#include <ostream>
#include <chrono>
#include <string>

namespace dtpp
{

struct API_DTPP time_t
{
    time_t() { }
    time_t(unsigned hh, unsigned mm, unsigned ss, unsigned ms=0)
    : hour{hh}
    , minute{mm}
    , second{ss}
    , millisecond{ms}
    { }

    unsigned int hour = 0;
    unsigned int minute = 0;
    unsigned int second = 0;
    unsigned int millisecond = 0;

    bool is_valid() const;
    std::chrono::hours to_hours() const;
    std::chrono::minutes to_minutes() const;
    std::chrono::seconds to_seconds() const;
    std::chrono::milliseconds to_millis() const;

    static time_t from_string(const std::string& str, const char* fmt = "%T");

    bool operator==(const time_t& t) const;
    bool operator!=(const time_t& t) const;
    bool operator<(const time_t& t) const;
    bool operator>(const time_t& t) const;
    bool operator<=(const time_t& t) const;
    bool operator>=(const time_t& t) const;
};

API_DTPP std::ostream& operator<<(std::ostream& os, const time_t& t);

}