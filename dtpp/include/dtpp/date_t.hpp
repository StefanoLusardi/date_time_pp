#pragma once

#include "api.hpp"
#include <ostream>
#include <chrono>
#include <string>

namespace dtpp
{
struct date_t;
API_DTPP date_t today();
API_DTPP date_t tomorrow();

struct API_DTPP date_t 
{
    date_t() { }
    date_t(int y, unsigned m, unsigned d)
    : year{y}
    , month{m}
    , day{d}
    { }
    
    int year = 0;
    unsigned int month = 0;
    unsigned int day = 0;

    bool is_valid() const;
    std::chrono::system_clock::time_point time_point() const;

    static date_t from_string(const std::string& str, const char* fmt = "%F");
    std::string to_string() const;

    bool operator==(const date_t& d) const;
    bool operator!=(const date_t& d) const;
    bool operator<(const date_t& d) const;
    bool operator>(const date_t& d) const;
    bool operator<=(const date_t& d) const;
    bool operator>=(const date_t& d) const;
};

API_DTPP std::ostream& operator<<(std::ostream& os, const date_t& d);

}