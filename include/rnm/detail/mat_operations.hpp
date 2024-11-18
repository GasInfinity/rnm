#ifndef _RENA_MATHEMATICS_DETAIL_MAT_OPERATIONS_HPP_
#define _RENA_MATHEMATICS_DETAIL_MAT_OPERATIONS_HPP_

#include "base.hpp"
#include "common.hpp"

#include "mat.hpp"

#include <cstddef>

namespace rnm
{
    namespace detail
    {
        template<typename T, std::size_t R, std::size_t C, std::size_t... I>
        rnm_forceinline constexpr mat<T, C, R> mat_transpose_helper(const mat<T, R, C>& rhs, const std::index_sequence<I...>&)
        { return mat<T, C, R>((rhs[(I % C), (I / C)])...); }

        template<typename T, std::size_t N, std::size_t MR, std::size_t MC, std::size_t... I>
        rnm_forceinline constexpr mat<T, N-1, N-1> mat_minor_helper(const mat<T, N, N>& lhs, const std::index_sequence<I...>&)
        { return mat<T, N-1, N-1>((lhs[((I / (N-1)) < MR ? (I / (N-1)) : (I / (N-1)) + 1), ((I % (N-1)) < MC ? (I % (N-1)) : (I % (N-1)) + 1)])...); }

        template<typename T, std::size_t... I> rnm_forceinline constexpr T determinant_helper(const mat<T, 1, 1>& lhs, const std::index_sequence<I...>&)
        { return lhs[0]; }

        template<typename T, std::size_t N, std::size_t... I> rnm_forceinline constexpr T determinant_helper(const mat<T, N, N>& lhs, const std::index_sequence<I...>&)
        { return ((static_cast<T>((I % 2) != 0 ? -1 : 1) * lhs[I] * ::rnm::determinant(::rnm::minor<0, I>(lhs))) + ...); }

        template<typename T, std::size_t N, std::size_t... I>
        rnm_forceinline constexpr mat<T, N, N> adjugate_helper(const mat<T, N, N>& lhs, const std::index_sequence<I...>&)
        { return mat<T, N, N>((static_cast<T>((((I / N) + (I % N)) % 2) != 0 ? -1 : 1) * ::rnm::determinant(minor<I / N, I % N>(lhs)))...); }
    } // namespace detail

    template<typename T, std::size_t R, std::size_t C> inline constexpr mat<T, C, R> transpose(const mat<T, R, C>& lhs)
    { return detail::mat_transpose_helper(lhs, std::make_index_sequence<R*C>{}); }
    
    template<std::size_t MR, std::size_t MC, typename T, std::size_t N> inline constexpr mat<T, N-1, N-1> minor(const mat<T, N, N>& lhs)
    { return detail::mat_minor_helper<T, N, MR, MC>(lhs, std::make_index_sequence<(N-1)*(N-1)>{}); }
    
    template<typename T, std::size_t N> inline constexpr T determinant(const mat<T, N, N>& lhs)
    { return detail::determinant_helper(lhs, std::make_index_sequence<N>{}); }
    
    template<typename T, std::size_t N> inline constexpr mat<T, N, N> adjugate(const mat<T, N, N>& lhs)
    { return detail::adjugate_helper(lhs, std::make_index_sequence<N*N>{}); }
    
    template<typename T, std::size_t N> inline constexpr bool has_inverse(const mat<T, N, N>& lhs)
    { return determinant(lhs) != static_cast<T>(0); }
    
    template<typename T, std::size_t N> inline constexpr mat<T, N, N> inverse(const mat<T, N, N>& lhs)
    { return (1 / determinant(lhs)) * transpose(adjugate(lhs)); }
} // namespace rnm

#endif // _RENA_MATHEMATICS_DETAIL_MAT_OPERATIONS_HPP_
