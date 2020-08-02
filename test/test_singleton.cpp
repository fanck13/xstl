
#include <numeric>
#include "catch2/catch.hpp"

#include "singleton.h"

class manager:public xstl::singleton<manager>{
public:
    static int static_method(){
        return 5;
    }

    static int a;
};

int manager::a = 6;

TEST_CASE("construct a singleton", "test singleton"){
    //auto& ins = xstl::singleton<int>::get_instance();
    //CHECK(ins == 0);

    auto& ins = manager::get_instance();
    CHECK(ins.a == 6);
    CHECK(ins.static_method() == 5);
}

