#pragma once

#include <thread>
#include <stdexcept>
#include "common.h"

XSTL_NAMESPACE_BEGIN

class scoped_thread
{
private:
    std::thread t;

public:
    explicit scoped_thread(std::thread _t) : t(std::move(_t))
    {
        if(!t.joinable())
        {
            throw std::logic_error("The thread can't be joined!");
        }
    }

    ~scoped_thread()
    {
        t.join();
    }

    scoped_thread(const scoped_thread&) = delete;
    scoped_thread& operator=(const scoped_thread&) = delete;

};
XSTL_NAMESPACE_END