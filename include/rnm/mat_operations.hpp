#ifndef _RENA_MATHEMATICS_MAT_OPERATIONS_HPP_
#define _RENA_MATHEMATICS_MAT_OPERATIONS_HPP_

#include "mat.hpp"

#include <cstddef>

namespace rnm
{
    template<typename T, std::size_t R, std::size_t C> inline constexpr mat<T, C, R> transpose(const mat<T, R, C>& lhs);
    template<std::size_t MR, std::size_t MC, typename T, std::size_t N> inline constexpr mat<T, N-1, N-1> minor(const mat<T, N, N>& lhs);
    template<typename T, std::size_t N> inline constexpr T determinant(const mat<T, N, N>& lhs);
    template<typename T, std::size_t N> inline constexpr mat<T, N, N> adjugate(const mat<T, N, N>& lhs);
    template<typename T, std::size_t N> inline constexpr bool has_inverse(const mat<T, N, N>& lhs);
    template<typename T, std::size_t N> inline constexpr mat<T, N, N> inverse(const mat<T, N, N>& lhs);
}

#include "detail/mat_operations.hpp"

#endif // _RENA_MATHEMATICS_MAT_OPERATIONS_HPP_
