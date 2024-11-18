#ifndef _RENA_MATHEMATICS_VEC_HPP_
#define _RENA_MATHEMATICS_VEC_HPP_

#include <cstddef>

namespace rnm
{
    template<typename T, std::size_t N> requires (N != 0)
    struct vec;

    template<typename T, std::size_t N> inline constexpr vec<T, N>& operator+=(vec<T, N>& lhs, const vec<T, N>& rhs);
    template<typename T, std::size_t N> inline constexpr vec<T, N>& operator-=(vec<T, N>& lhs, const vec<T, N>& rhs);
    template<typename T, std::size_t N> inline constexpr vec<T, N>& operator*=(vec<T, N>& lhs, T rhs);
    template<typename T, std::size_t N> inline constexpr vec<T, N>& operator/=(vec<T, N>& lhs, T rhs);

    template<typename T, std::size_t N> inline constexpr vec<T, N> operator-(const vec<T, N>& lhs);
    template<typename T, std::size_t N> inline constexpr vec<T, N> operator+(const vec<T, N>& lhs, const vec<T, N>& rhs);
    template<typename T, std::size_t N> inline constexpr vec<T, N> operator-(const vec<T, N>& lhs, const vec<T, N>& rhs);
    template<typename T, std::size_t N> inline constexpr vec<T, N> operator*(const vec<T, N>& lhs, T rhs);
    template<typename T, std::size_t N> inline constexpr vec<T, N> operator*(T lhs, const vec<T, N>& rhs);
    template<typename T, std::size_t N> inline constexpr vec<T, N> operator/(const vec<T, N>& lhs, T rhs);

    template<typename T, std::size_t N> inline constexpr vec<T, N> mul(const vec<T, N>& lhs, const vec<T, N>& rhs);
    template<typename T, std::size_t N> inline constexpr T dot(const vec<T, N>& lhs, const vec<T, N>& rhs);
    template<typename T, std::size_t N> inline constexpr T length_sqr(const vec<T, N>& lhs);
    template<typename T, std::size_t N> inline constexpr T length(const vec<T, N>& lhs);
    template<typename T, std::size_t N> inline constexpr vec<T, N> normalized(const vec<T, N>& lhs);

    template<typename T, std::size_t N> inline constexpr T distance_sqr(const vec<T, N>& lhs, const vec<T, N>& rhs);
    template<typename T, std::size_t N> inline constexpr T distance(const vec<T, N>& lhs, const vec<T, N>& rhs);
    template<typename T, std::size_t N> inline constexpr vec<T, N> lerp(const vec<T, N>& lhs, const vec<T, N>& rhs, T t);

    template<typename T> inline constexpr vec<T, 3> cross(const vec<T, 3>& lhs, const vec<T, 3>& rhs);
    template<typename T> inline constexpr vec<T, 2> perpendicular_right(const vec<T, 2>& lhs);
    template<typename T> inline constexpr vec<T, 2> perpendicular_left(const vec<T, 2>& lhs);

    template<typename T = float> using vec1 = vec<T, 1>;
    template<typename T = float> using vec2 = vec<T, 2>;
    template<typename T = float> using vec3 = vec<T, 3>;
    template<typename T = float> using vec4 = vec<T, 4>;
}

#include "detail/vec.hpp"

#endif // _RENA_MATHEMATICS_VEC_HPP_
