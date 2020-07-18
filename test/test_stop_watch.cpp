#include "catch2/catch.hpp"

#include <thread>
#include "stop_watch.h"


TEST_CASE("Test default stop watch", "Stop watch test"){

    xstl::default_stop_watch sw;
    
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(5s);

    CHECK((sw.elapsed()/1000/1000) == 5);
}


TEST_CASE("Test different stop watchs", "Stop watch test"){

    xstl::stop_watch<std::chrono::microseconds> micro_sw; 
    xstl::stop_watch<std::chrono::nanoseconds> nano_sw; 
    xstl::stop_watch<std::chrono::milliseconds> millis_sw;

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(5s);

    CHECK((micro_sw.elapsed()/1000/1000) == 5);
    CHECK((nano_sw.elapsed()/1000/1000/1000) == 5);
    CHECK((millis_sw.elapsed()/1000) == 5);
}

TEST_CASE("Test stop watch restart", "Stop watch test") {
	xstl::stop_watch<std::chrono::microseconds> sw;

	using namespace std::chrono_literals;
	std::this_thread::sleep_for(5s);

	sw.restart();
	std::this_thread::sleep_for(5s);

	CHECK((sw.elapsed() / 1000 / 1000) == 5);
}

