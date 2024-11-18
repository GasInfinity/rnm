#ifndef _RENA_MATHEMATICS_DETAIL_COMMON_HPP_
#define _RENA_MATHEMATICS_DETAIL_COMMON_HPP_

#include "base.hpp"

#include <utility>

namespace rnm
{
    namespace detail
    {
        template<typename U, std::size_t... I> rnm_forceinline constexpr U neg_helper(const U& lhs, const std::index_sequence<I...>&)
        { return U((-lhs[I])...); }

        template<typename U, std::size_t... I> rnm_forceinline constexpr U add_helper(const U& lhs, const U& rhs, const std::index_sequence<I...>&)
        { return U((lhs[I] + rhs[I])...); }

        template<typename U, std::size_t... I> rnm_forceinline constexpr U sub_helper(const U& lhs, const U& rhs, const std::index_sequence<I...>&)
        { return U((lhs[I] - rhs[I])...); }

        template<typename U, std::size_t... I> rnm_forceinline constexpr U mul_helper(const U& lhs, const U& rhs, const std::index_sequence<I...>&)
        { return U((lhs[I] * rhs[I])...); }

        template<typename U, typename T, std::size_t... I> rnm_forceinline constexpr U mul_helper(const U& lhs, const T& rhs, const std::index_sequence<I...>&)
        { return U((lhs[I] * rhs)...); }

        template<typename U, typename T, std::size_t... I> rnm_forceinline constexpr U div_helper(const U& lhs, const T& rhs, const std::index_sequence<I...>&)
        { return U((lhs[I] / rhs)...); }

        template<typename T, std::size_t N, std::size_t... I> rnm_forceinline constexpr T dot_helper(const vec<T, N>& lhs, const vec<T, N>& rhs, const std::index_sequence<I...>&)
        { return ((lhs[I] * rhs[I]) + ...); }

        template<typename U, std::size_t... I> rnm_forceinline constexpr U& addr_helper(U& lhs, const U& rhs, const std::index_sequence<I...>&)
        { return (void(lhs[I] = (lhs[I] + rhs[I])), ...), lhs; }

        template<typename U, std::size_t... I> rnm_forceinline constexpr U& subr_helper(U& lhs, const U& rhs, const std::index_sequence<I...>&)
        { return (void(lhs[I] = (lhs[I] - rhs[I])), ...), lhs; }

        template<typename T, typename U, std::size_t... I> rnm_forceinline constexpr U& mulr_helper(U& lhs, T rhs, const std::index_sequence<I...>&)
        { return (void(lhs[I] = (lhs[I] * rhs)), ...), lhs; }

        template<typename T, typename U, std::size_t... I> rnm_forceinline constexpr U& divr_helper(U& lhs, T rhs, const std::index_sequence<I...>&)
        { return (void(lhs[I] = (lhs[I] / rhs)), ...), lhs; }

        template<typename T, typename U, std::size_t... I>
        rnm_forceinline constexpr T cast_compound_to_compound_helper(const U& lhs, const std::index_sequence<I...>&)
        { return T(lhs[I]...); }
    } // namespace detail
} // namespace rnm

#endif // _RENA_MATHEMATICS_DETAIL_COMMON_HPP_
