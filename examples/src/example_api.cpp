#include <dtpp/dtpp.hpp>
#include <iostream>

int main()
{
	const auto tt_1 = dtpp::time_t::from_string("12:13:14.123");
	const auto tt_2 = dtpp::time_t::from_string("12:13:14.1234567");
	const auto tt_3 = dtpp::time_t::from_string("12:13:14", "%H:%M:%S"); // "%T" 24-hour clock
	const auto tt_4 = dtpp::time_t::from_string("12:13:14.123", "%R"); // "%H:%M"
	const auto tt_5 = dtpp::time_t::from_string("12:13:14", "%I:%M:%S"); // 12-hour clock
	std::cout << "Time from string: " << tt_1 << std::endl;
	std::cout << "Time from string: " << tt_2 << std::endl;
	std::cout << "Time from string: " << tt_3 << std::endl;
	std::cout << "Time from string: " << tt_4 << std::endl;
	std::cout << "Time from string: " << tt_5 << "\n\n" << std::endl;

	const auto dd_1 = dtpp::date_t::from_string("2020-03-31");
	const auto dd_2 = dtpp::date_t::from_string("2020-Mar-31", "%Y-%b-%d");
	const auto dd_3 = dtpp::date_t::from_string("03/31/2020", "%m/%d/%y"); // "%D"
	// const auto dd_4 = dtpp::date_t::from_string("Mar-31-2020", "%b-%d-%Y");
	std::cout << "Time from string: " << dd_1 << std::endl;
	std::cout << "Time from string: " << dd_2 << std::endl;
	std::cout << "Time from string: " << dd_3 << std::endl;
	// std::cout << "Time from string: " << dd_4 << std::endl;


	/*
	const auto ts = dtpp::datetime_t::timestamp();
	std::cout << "UTC now: " << ts << std::endl;

	const auto ts_d = dtpp::datetime_t::timestamp("%F");
	std::cout << "UTC now: " << ts_d << " [date]" << std::endl;

	const auto ts_t = dtpp::datetime_t::timestamp("%T");
	std::cout << "UTC now: " << ts_t << " [time]" << std::endl;

	dtpp::datetime_t dt{ 2015, 8, 27, 10, 3, 40, 12 };

	const dtpp::date_t d = dt.date();
	std::cout << "From datetime_t [2015, 8, 27, 10, 3, 40, 12]: " << d << " [date]" << std::endl;

	const dtpp::time_t t = dt.time();
	std::cout << "From datetime_t [2015, 8, 27, 10, 3, 40, 12]: " << t << " [time]" << "\n\n" << std::endl;

	const dtpp::datetime_t str_dt = dtpp::datetime_t::from_string("2015-01-01T01:01:01.123");
	std::cout << "From string [2015-01-01T01:01:01.123]: " << str_dt << std::endl;

	const dtpp::date_t str_d = str_dt.date();
	std::cout << "From string [2015-01-01T01:01:01.123]: " << str_d << " [date]" << std::endl;

	const dtpp::time_t str_t = str_dt.time();
	std::cout << "From string [2015-01-01T01:01:01.123]: " << str_t << " [time]" << "\n\n" << std::endl;

	const dtpp::datetime_t utc_now = dtpp::datetime_t::utc_now();
	std::cout << "Now: " << utc_now << std::endl;

	const dtpp::date_t utc_now_d = utc_now.date();
	std::cout << "Now: " << utc_now_d << " [date]" << std::endl;

	const dtpp::time_t utc_now_t = utc_now.time();
	std::cout << "Now: " << utc_now_t << " [time]" << "\n\n" << std::endl;

	const auto dt_tp = utc_now.time_point();
	std::cout << dt_tp.time_since_epoch().count() << std::endl;
	std::cout << std::chrono::system_clock::now().time_since_epoch().count() << std::endl;
	*/

	return 0;
}

