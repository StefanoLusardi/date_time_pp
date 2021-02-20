#pragma once

#include <date/date.h>

#include "api.hpp"
#include "date_t.hpp"
#include "time_t.hpp"

namespace dtpp
{
template<typename Duration>
inline time_t make_time(const date::hh_mm_ss<Duration>& t)
{
    return { unsigned(t.hours().count()), unsigned(t.minutes().count()), unsigned(t.seconds().count()), unsigned(t.subseconds().count()) };
}

inline date_t make_date(const date::year_month_day& d)
{
    return { int(d.year()), unsigned(d.month()), unsigned(d.day()) };
}


}