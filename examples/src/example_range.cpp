#include <dtpp/dtpp.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
struct range_t
{
    T min;
    T max;
    inline bool contains(const T& value) const { return min <= value && value < max; }
};
using time_range = range_t<dtpp::time_t>;

int main()
{
    // millis: 1613580420000
    // seconds: 1613580420
    // date: 17/02/2021 - 16:47:00 (UTC)

    auto from_time1 = std::chrono::floor<std::chrono::minutes>(std::chrono::system_clock::from_time_t(1613580420));
    std::chrono::time_point<std::chrono::system_clock> from_time2 = std::chrono::system_clock::from_time_t(1613580420);
    
    auto epoch1 = std::chrono::floor<std::chrono::seconds>(from_time1).time_since_epoch().count();
    auto epoch2 = std::chrono::floor<std::chrono::seconds>(from_time2).time_since_epoch().count();

    auto ftp = dtpp::datetime_t::from_time_point(from_time2);
    std::cout << "From time point (1613580420 seconds): "<< ftp << std::endl;

    auto dt = dtpp::utc_now();
    auto tp_1 = dt.time_point<std::chrono::system_clock::time_point>();
    auto tp_2 = dt.time_point<std::chrono::steady_clock::time_point>();
    
    std::cout << "NOW [ms]: " << "\t\t" << std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count() << std::endl;

    auto t1 = dtpp::time_t(6,0,0);
    std::cout << "t1  [ms]: " << t1 << "\t" << t1.to_millis().count() << std::endl;

    auto t2 = dtpp::time_t(6,57,58,59);
    std::cout << "t2  [ms]: " << t2 << "\t" << t2.to_millis().count() << std::endl;

    time_range t_r{t1, t2};

    auto now = dtpp::utc_now().time();
    std::cout << "now [ms]: " << now << "\t" << now.to_millis().count() << std::endl;

    bool c = t_r.contains(now);    
    std::cout << "\ncontains: " << std::boolalpha << c << "\n" << std::endl;

    std::cout << " t1 <  now: " << std::boolalpha << (t1<now)  << std::endl;
    std::cout << " t1 <= now: " << std::boolalpha << (t1<=now) << std::endl;
    std::cout << " t1 >  now: " << std::boolalpha << (t1>now)  << std::endl;
    std::cout << " t1 >= now: " << std::boolalpha << (t1>=now) << std::endl;

    std::cout << " t2 <  now: " << std::boolalpha << (t2<now)  << std::endl;
    std::cout << " t2 <= now: " << std::boolalpha << (t2<=now) << std::endl;
    std::cout << " t2 >  now: " << std::boolalpha << (t2>now)  << std::endl;
    std::cout << " t2 >= now: " << std::boolalpha << (t2>=now) << std::endl;


    std::vector<time_range> times = {
        { dtpp::time_t( 0,0,0), dtpp::time_t( 7,0,0) },
        { dtpp::time_t( 7,0,0), dtpp::time_t(7,20,0) },
        { dtpp::time_t(7,20,0), dtpp::time_t(7,30,0) },
        { dtpp::time_t(7,30,0), dtpp::time_t(7,40,0) },
    };

    auto time_now = dtpp::utc_now().time();
    std::cout << "\nTime Now: " << time_now << std::endl;
    auto tr = std::find_if(times.begin(), times.end(), [time_now](const auto& r) {
        std::cout << "\nTime Range: " << std::endl;
        std::cout << " * min: " << r.min << std::endl;
        std::cout << " * max: " << r.max << std::endl;
        if(r.contains(time_now))
        {
            std::cout << " - IN" << std::endl;
            return true;
        }
        else
        {
            std::cout << " - OUT" << std::endl;
            return false;
        }
    });

	std::cout << "\nTime Range: " << tr->min << " - " << tr->max << std::endl;

	return 0;
}

