#pragma once

#include <algorithm>
#include "common.h"

XSTL_NAMESPACE_BEGIN

template <typename Iterator, typename T>
struct accumulate_block
{
    void operator()(Iterator first, Iterator last, T& result)
    {
        result = std::accumulate(first, last, result);
    }
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    unsigned long const length = std::distance(first, last);

    if(length == 1) return init;

    unsigned long const min_per_thread = 25;
    unsigned long const max_thread = 

}

XSTL_NAMESPACE_END