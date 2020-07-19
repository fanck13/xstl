#include <vector>
#include <catch2/catch.hpp>
#include "parallel_algorithm.h"

TEST_CASE("test parallel accumulate", "test parallel algorithm") 
{
    std::vector<int> vec;
    vec.reserve(1024);
    for (int i = 0; i < 1024; i++) 
    {
        vec.push_back(i);
    }
    auto result = xstl::parallel_accumulate(std::begin(vec), std::end(vec), 0);
    CHECK(523776 == result);
}