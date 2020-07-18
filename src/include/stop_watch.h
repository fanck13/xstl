#pragma once

#include <chrono>
#include "common.h"

XSTL_NAMESPACE_BEGIN

template <typename T , typename Enable = void>
class stop_watch;

template<typename T>
class stop_watch<T, typename std::enable_if<std::is_same<T, std::chrono::microseconds>::value || 
                                            std::is_same<T, std::chrono::nanoseconds>::value || 
                                            std::is_same<T, std::chrono::milliseconds>::value>::type>
{
    using high_resolution_clock = std::chrono::high_resolution_clock;
public:
    stop_watch() {
        _start = high_resolution_clock::now();
    }

    auto elapsed() {
        auto _now = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<T>(_now - _start).count();
    }

    void restart(){
        _start = high_resolution_clock::now();
    }

    ~stop_watch() { }

private:
    std::chrono::high_resolution_clock::time_point _start;
};

using default_stop_watch = stop_watch<std::chrono::microseconds>;
XSTL_NAMESPACE_END