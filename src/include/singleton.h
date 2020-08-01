#pragma once

#include <memory>
#include "common.h"

XSTL_NAMESPACE_BEGIN

template <class T>
class singleton
{
public:
    static T& get_instance()
    {
        if(p == nullptr)
            p = std::unique_ptr<T>(new T);
        return *p;
    }

protected:
    singleton() = default;
    static std::unique_ptr<T> p;
};

template <class T>
std::unique_ptr< T > singleton<T>::p;

XSTL_NAMESPACE_END