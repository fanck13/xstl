#pragma once

#include <utility>
#include <tuple>
#include <cstdio>

#include "common.h"

XSTL_NAMESPACE_BEGIN

namespace detail
{
    template <typename ... Ts>
    struct container : std::tuple<Ts...>
    {
        container(std::tuple<Ts...>&& tuple)
                : std::tuple<Ts...>(std::move(tuple))
        {}

        container& operator=(const container& other)
        {
            std::tuple<Ts...>::operator=(std::tuple<std::remove_reference_t<Ts>...>(other));
            return *this;
        }

        template <typename U>
        friend container<Ts&..., U&> operator,(std::tuple<Ts&...> lhs, U& rhs)
        {
            return std::tuple_cat(lhs, std::tie(rhs));
        }
    };
}

template <typename Derived>
struct enable_swap
{
    template <typename U>
    friend detail::container<Derived&, U&> operator,(Derived& lhs, U& rhs)
    {
        return std::tie(lhs, rhs);
    }
};

XSTL_NAMESPACE_END