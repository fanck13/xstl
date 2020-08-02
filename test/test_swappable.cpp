#include "catch2/catch.hpp"
#include "swappable.h"

struct swappable_int : xstl::enable_swap<swappable_int>
{
    int value;
    swappable_int(int value)
            : value(value) {}

    operator int() const
    {
        return value;
    }
};

TEST_CASE("swap a b", "test swapable tuple"){
    swappable_int a = 1;
    swappable_int b = 2;

    CHECK(a == 1);
    CHECK(b == 2);

    (a, b) = (b, a);
    CHECK(a == 2);
    CHECK(b == 1);
}
