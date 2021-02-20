#pragma once

#include <ostream>
#include <chrono>
#include <string>

#include "api.hpp"
#include "date_t.hpp"
#include "time_t.hpp"

namespace dtpp
{
class datetime_t;
API_DTPP datetime_t utc_now();
API_DTPP std::string timestamp(const char* fmt = "%FT%T");

class API_DTPP datetime_t
{
private:
    date_t _d;
    time_t _t;

public:
    datetime_t() { }
    datetime_t(int y, unsigned m, unsigned d, unsigned hh, unsigned mm, unsigned ss, unsigned ms=0)
    : _d{date_t{y, m, d}}
    , _t{time_t{hh, mm, ss, ms}}
    { }

    datetime_t(date_t date, time_t time)
    : _d{date}
    , _t{time}
    { }

    bool is_valid() const { return _d.is_valid() && _t.is_valid(); };

    int year() const { return _d.year; }
    unsigned int month() const { return _d.month; }
    unsigned int day() const { return _d.day; }
    unsigned int hour() const { return _t.hour; }
    unsigned int minute() const { return _t.minute; }
    unsigned int second() const { return _t.second; }
    unsigned int millisecond() const { return _t.millisecond; }

    static datetime_t from_string(const std::string& str, const char* fmt = "%FT%T");
    static datetime_t from_time_point(const std::chrono::system_clock::time_point& tp);
   
    date_t date() const { return _d; }
    void set_date(date_t d) { _d = d; }

    time_t time() const { return _t; }
    void set_time(time_t t) { _t = t; }

    template<class TimePoint_t>
    TimePoint_t time_point() const;
};

template<> 
std::chrono::system_clock::time_point 
API_DTPP datetime_t::time_point<std::chrono::system_clock::time_point>() const;

template<> 
std::chrono::steady_clock::time_point 
API_DTPP datetime_t::time_point<std::chrono::steady_clock::time_point>() const;

API_DTPP std::ostream& operator<<(std::ostream& os, const datetime_t& dt);

}