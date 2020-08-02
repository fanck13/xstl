 #pragma once

#include <thread>
#include "common.h"

XSTL_NAMESPACE_BEGIN

class thread_guard
{
private:
    std::thread& t;
public:
    explicit thread_guard(std::thread& _t):t(_t)
    { }

    ~thread_guard()
    {
        if(t.joinable()){
            t.join();
        }
    }

    thread_guard(const thread_guard& ) = delete;
    thread_guard& operator=(const thread_guard&) = delete;
};

XSTL_NAMESPACE_END
