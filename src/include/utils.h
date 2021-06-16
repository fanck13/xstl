#pragma once

#include "common.h"
#include <iostream>

#include <functional>
#include <chrono>

XSTL_NAMESPACE_BEGIN

class utils
{
public:

    template <typename Container>
    static void print(const Container& c, std::ostream& out = std::cout, const char* delim = " ")
    {
        std::ostream_iterator<typename Container::value_type> iter(out, delim);
        std::copy(std::cbegin(c), std::cend(c), iter);
        out << "\n";   
    }

    template <class F, class... Args>
    std::pair<double, std::invoke_result_t<F, Args...>> time_span(F&& f, Args&&... args)
    {
        std::pair<int, std::invoke_result_t<F, Args...>> result;
        auto start = std::chrono::high_resolution_clock::now();
        result.second = std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        result.first = std::chrono::duration<double, std::milli>(end - start).count();
        return result;
    }
};

XSTL_NAMESPACE_END
