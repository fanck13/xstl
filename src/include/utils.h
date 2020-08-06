#pragma once

#include "common.h"
#include <iostream>

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
};

XSTL_NAMESPACE_END
