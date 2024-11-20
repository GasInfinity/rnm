#ifndef _RENA_MATHEMATICS_MAT_HPP_
#define _RENA_MATHEMATICS_MAT_HPP_

#include "vec.hpp"

#include <type_traits>
#include <cstddef>

namespace rnm
{
    template<typename T, std::size_t R, std::size_t C> requires (R != 0 && C != 0)
    struct mat;

    template<typename T, std::size_t R, std::size_t C> inline constexpr mat<T, R, C>& operator+=(mat<T, R, C>& lhs, const mat<T, R, C>& rhs);
    template<typename T, std::size_t R, std::size_t C> inline constexpr mat<T, R, C>& operator-=(mat<T, R, C>& lhs, const mat<T, R, C>& rhs);
    template<typename T, typename U, std::size_t R, std::size_t C> inline constexpr mat<T, R, C>& operator*=(mat<T, R, C>& lhs, U rhs) requires std::is_convertible_v<U, T>;
    template<typename T, typename U, std::size_t R, std::size_t C> inline constexpr mat<T, R, C>& operator/=(mat<T, R, C>& lhs, U rhs) requires std::is_convertible_v<U, T>;

    template<typename T, std::size_t R, std::size_t C> inline constexpr mat<T, R, C> operator -(const mat<T, R, C>& lhs);
    template<typename T, std::size_t R, std::size_t C> inline constexpr mat<T, R, C> operator +(const mat<T, R, C>& lhs, const mat<T, R, C>& rhs);
    template<typename T, std::size_t R, std::size_t C> inline constexpr mat<T, R, C> operator -(const mat<T, R, C>& lhs, const mat<T, R, C>& rhs);
    template<typename T, typename U, std::size_t R, std::size_t C> inline constexpr mat<T, R, C> operator *(const mat<T, R, C>& lhs, U rhs) requires std::is_convertible_v<U, T>;
    template<typename T, typename U, std::size_t R, std::size_t C> inline constexpr mat<T, R, C> operator *(U lhs, const mat<T, R, C>& rhs) requires std::is_convertible_v<U, T>;
    template<typename T, typename U, std::size_t R, std::size_t C> inline constexpr mat<T, R, C> operator /(const mat<T, R, C>& lhs, U rhs) requires std::is_convertible_v<U, T>;

    template<typename T, std::size_t CR, std::size_t R, std::size_t C> inline constexpr mat<T, R, C> operator *(const mat<T, R, CR>& lhs, const mat<T, CR, C>& rhs);
    
    template<typename T, std::size_t N> inline constexpr mat<T, N, 1> vec_castr(const vec<T, N>& lhs);
    template<typename T, std::size_t N> inline constexpr mat<T, 1, N> vec_castc(const vec<T, N>& lhs);
    template<typename T, std::size_t N> inline constexpr vec<T, N> mat_cast(const mat<T, N, 1>& lhs);
    template<typename T, std::size_t N> inline constexpr vec<T, N> mat_cast(const mat<T, 1, N>& lhs);
    template<typename T, std::size_t N, std::size_t R> inline constexpr vec<T, N> operator*(const mat<T, R, N>& lhs, const vec<T, N>& rhs);
    template<typename T, std::size_t N, std::size_t C> inline constexpr vec<T, N> operator*(const vec<T, N>& lhs, const mat<T, N, C>& rhs);

    template<typename T = float> using mat1 = mat<T, 1, 1>;
    template<typename T = float> using mat2 = mat<T, 2, 2>;
    template<typename T = float> using mat3 = mat<T, 3, 3>;
    template<typename T = float> using mat4 = mat<T, 4, 4>;
}

#include "detail/mat.hpp"

#endif // _RENA_MATHEMATICS_MAT_HPP_
