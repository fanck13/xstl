#pragma once

#include "common.h"
#include <atomic>

XSTL_NAMESPACE_BEGIN

class spin_lock
{
public:
    spin_lock(){}

    void lock()
    {
        while(flag.test_and_set(std::memory_order_acquire));
    }

    void unlock()
    {
        flag.clear(std::memeory_order_release);
    }

private:
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
};


XSTL_NAMESPACE_END