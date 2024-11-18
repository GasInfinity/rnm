#ifndef _RENA_MATHEMATICS_DETAIL_VEC_HPP_
#define _RENA_MATHEMATICS_DETAIL_VEC_HPP_

#include "base.hpp"
#include "common.hpp"

#include <type_traits>
#include <utility>
#include <cstddef>
#include <cmath>

namespace rnm
{
    namespace detail
    {
        template<typename T, std::size_t N, std::size_t I>
        struct accessor_helper
        {
            T data[N];

            rnm_forceinline constexpr accessor_helper<T, N, I>& operator=(const T& rhs) { this->data[I] = rhs; return *this; }
            accessor_helper<T, N, I>& operator=(const accessor_helper<T, N, I>& rhs) = delete;

            rnm_forceinline constexpr operator T&() { return this->data[I]; }
            rnm_forceinline constexpr operator const T&() const { return this->data[I]; }
        };

        template<typename T, std::size_t N, std::size_t O, std::size_t... I>
        struct swizzle_helper
        {
            T data[N];

            rnm_forceinline constexpr operator const vec<T, O>() const { return vec<T, O>(this->data[I]...); }
        };
    } // namespace detail

    template<typename T, std::size_t N> requires (N != 0)
    struct vec
    {
        using scalar = T;
        constexpr static std::size_t data_size = N;

        T data[N];

        constexpr vec() : data() { }
        constexpr explicit vec(const T* _data) : vec(_data, std::make_index_sequence<N>{}) { }
        constexpr explicit vec(T _scalar) : vec(_scalar, std::make_index_sequence<N>{}) { }
        template<typename... U> constexpr vec(U... _args) requires (sizeof...(_args) == N && (std::is_convertible_v<U, T> && ...)) : data{static_cast<T>(_args)...} { }

        constexpr T& operator[](std::size_t n) { return this->data[n]; }
        constexpr const T& operator[](std::size_t n) const { return this->data[n]; }

        template<typename U> constexpr explicit operator vec<U, N>() const { return cast_helper(std::make_index_sequence<N>{}); }
    private:
        template<std::size_t... I> constexpr explicit vec(const T* _data, const std::index_sequence<I...>&) : data{(_data[I])...} { }
        template<std::size_t... I> constexpr explicit vec(T _scalar, const std::index_sequence<I...>&) : data{((void)I, _scalar)...} { }
        template<typename U, std::size_t... I> rnm_forceinline constexpr vec<U, N> cast_helper(const std::index_sequence<I...>&) const { return vec<U, N>(static_cast<U>(data[I])...); }
    };

    template<typename T>
    struct vec<T, 1>
    {
        using scalar = T;
        constexpr static std::size_t data_size = 1;

        union { T data[1]; detail::accessor_helper<T, 1, 0> x, r, s; };

        constexpr vec() : data() { }
        constexpr explicit vec(const T* _data) : data{_data[0]} { }
        constexpr vec(T _x) : data{_x} { }

        rnm_forceinline constexpr T& operator[](std::size_t n) { return this->data[n]; }
        rnm_forceinline constexpr const T& operator[](std::size_t n) const { return this->data[n]; }
        rnm_forceinline constexpr operator const T&() const { return this->data[0]; }

        template<typename U> rnm_forceinline constexpr explicit operator vec<U, 1>() const { return vec<T, 1>(static_cast<U>(data[0])); }
    };

    template<typename T>
    struct vec<T, 2>
    {
        using scalar = T;
        constexpr static std::size_t data_size = 2;

        union
        {
            T data[2];
            detail::accessor_helper<T, 2, 0> x, r, s;
            detail::accessor_helper<T, 2, 1> y, g, t;
        };

        constexpr vec() : data() { }
        constexpr explicit vec(const T* _data) : data{_data[0], _data[1]} { }
        constexpr explicit vec(T _scalar) : data{_scalar, _scalar} { }
        constexpr vec(T _x, T _y): data{_x, _y} { }
        constexpr vec(vec<T, 1> _x, T _y) : data{_x[0], _y} { }

        rnm_forceinline constexpr T& operator[](std::size_t n) { return data[n]; }
        rnm_forceinline constexpr const T& operator[](std::size_t n) const { return data[n]; }

        template<typename U> inline constexpr explicit operator vec<U, 2>() const { return vec<T, 2>(static_cast<U>(data[0]), static_cast<U>(data[1])); }
    };

    template<typename T>
    struct vec<T, 3>
    {
        using scalar = T;
        constexpr static std::size_t data_size = 3;

        union
        {
            T data[3];
            detail::accessor_helper<T, 3, 0> x, r, s;
            detail::accessor_helper<T, 3, 1> y, g, t;
            detail::accessor_helper<T, 3, 2> z, b, p;
            detail::swizzle_helper<T, 3, 2, 0, 1> xy;
        };

        constexpr vec() : data() { }
        constexpr explicit vec(const T* _data) : data{_data[0], _data[1], _data[2]} { }
        constexpr explicit vec(T _scalar) : data{_scalar, _scalar, _scalar} { }
        constexpr vec(T _x, T _y, T _z) : data{_x, _y, _z} { }
        constexpr vec(vec<T, 1> _x, T _y, T _z) : data{_x[0], _y, _z} { }
        constexpr vec(vec<T, 2> _xy, T _z) : data{_xy[0], _xy[1], _z} { }

        rnm_forceinline constexpr T& operator[](std::size_t n) { return data[n]; }
        rnm_forceinline constexpr const T& operator[](std::size_t n) const { return data[n]; }

        template<typename U> constexpr explicit operator vec<U, 3>() const { return vec<T, 3>(static_cast<U>(data[0]), static_cast<U>(data[1]), static_cast<U>(data[2])); }
    };

    template<typename T>
    struct vec<T, 4>
    {
        using scalar_t = T;
        constexpr static std::size_t data_size = 4;

        union
        {
            T data[4];
            detail::accessor_helper<T, 4, 0> x, r, s;
            detail::accessor_helper<T, 4, 1> y, g, t;
            detail::accessor_helper<T, 4, 2> z, b, p;
            detail::accessor_helper<T, 4, 2> w, a, q;
            detail::swizzle_helper<T, 4, 2, 0, 1> xy;
            detail::swizzle_helper<T, 4, 3, 0, 1, 2> xyz;
        };

        constexpr vec() : data() { }
        constexpr explicit vec(const T* _data) : data{_data[0], _data[1], _data[2], _data[3]} { }
        constexpr explicit vec(T _scalar) : data{_scalar, _scalar, _scalar, _scalar} { }
        constexpr vec(T _x, T _y, T _z, T _w) : data{_x, _y, _z, _w} { }
        constexpr vec(vec<T, 1> _x, T _y, T _z, T _w) : data{_x[0], _y, _z, _w} { }
        constexpr vec(vec<T, 2> _xy, T _z, T _w) : data{_xy[0], _xy[1], _z, _w} { }
        constexpr vec(vec<T, 3> _xyz, T _w) : data{_xyz[0], _xyz[1], _xyz[2], _w} { }

        rnm_forceinline constexpr T& operator[](std::size_t n) { return data[n]; }
        rnm_forceinline constexpr const T& operator[](std::size_t n) const { return data[n]; }

        template<typename U> constexpr explicit operator vec<U, 4>() const { return vec<T, 4>(static_cast<U>(data[0]), static_cast<U>(data[1]), static_cast<U>(data[2]), static_cast<U>(data[3])); }
    };

    template<typename T, std::size_t N> inline constexpr vec<T, N>& operator+=(vec<T, N>& lhs, const vec<T, N>& rhs) { return detail::addr_helper(lhs, rhs, std::make_index_sequence<N>{}); }
    template<typename T, std::size_t N> inline constexpr vec<T, N>& operator-=(vec<T, N>& lhs, const vec<T, N>& rhs) { return detail::subr_helper(lhs, rhs, std::make_index_sequence<N>{}); }
    template<typename T, std::size_t N> inline constexpr vec<T, N>& operator*=(vec<T, N>& lhs, T rhs) { return detail::mulr_helper(lhs, rhs, std::make_index_sequence<N>{}); }
    template<typename T, std::size_t N> inline constexpr vec<T, N>& operator/=(vec<T, N>& lhs, T rhs) { return detail::divr_helper(lhs, rhs, std::make_index_sequence<N>{}); }

    template<typename T, std::size_t N> inline constexpr vec<T, N> operator-(const vec<T, N>& lhs) { return detail::neg_helper(lhs, std::make_index_sequence<N>{}); }
    template<typename T, std::size_t N> inline constexpr vec<T, N> operator+(const vec<T, N>& lhs, const vec<T, N>& rhs) { return detail::add_helper(lhs, rhs, std::make_index_sequence<N>{}); }
    template<typename T, std::size_t N> inline constexpr vec<T, N> operator-(const vec<T, N>& lhs, const vec<T, N>& rhs) { return detail::sub_helper(lhs, rhs, std::make_index_sequence<N>{}); }
    template<typename T, std::size_t N> inline constexpr vec<T, N> operator*(const vec<T, N>& lhs, T rhs) { return detail::mul_helper(lhs, rhs, std::make_index_sequence<N>{}); }
    template<typename T, std::size_t N> inline constexpr vec<T, N> operator*(T lhs, const vec<T, N>& rhs) { return detail::mul_helper(rhs, lhs, std::make_index_sequence<N>{}); }
    template<typename T, std::size_t N> inline constexpr vec<T, N> operator/(const vec<T, N>& lhs, T rhs) { return detail::div_helper(lhs, rhs, std::make_index_sequence<N>{}); }

    template<typename T, std::size_t N> inline constexpr vec<T, N> mul(const vec<T, N>& lhs, const vec<T, N>& rhs)
    { return detail::mul_helper(lhs, rhs, std::make_index_sequence<N>{}); }
    
    template<typename T, std::size_t N> inline constexpr T dot(const vec<T, N>& lhs, const vec<T, N>& rhs)
    { return detail::dot_helper(lhs, rhs, std::make_index_sequence<N>{}); }

    template<typename T, std::size_t N> inline constexpr T length_sqr(const vec<T, N>& lhs) { return dot(lhs, lhs); }
    template<typename T, std::size_t N> inline constexpr T length(const vec<T, N>& lhs) { return std::sqrt(length_sqr(lhs)); }
    template<typename T, std::size_t N> inline constexpr vec<T, N> normalized(const vec<T, N>& lhs) { return lhs / length(lhs); }

    template<typename T, std::size_t N> inline constexpr T distance_sqr(const vec<T, N>& lhs, const vec<T, N>& rhs) { return length_sqr(lhs - rhs); }
    template<typename T, std::size_t N> inline constexpr T distance(const vec<T, N>& lhs, const vec<T, N>& rhs) { return length(lhs - rhs); }
    template<typename T, std::size_t N> inline constexpr vec<T, N> lerp(const vec<T, N>& lhs, const vec<T, N>& rhs, T t) { return lhs + (rhs - lhs) * t; }

    template<typename T> inline constexpr vec<T, 3> cross(const vec<T, 3>& lhs, const vec<T, 3>& rhs)
    { return vec<T, 3>((lhs[1] * rhs[2]) - (rhs[2] * lhs[1]), (lhs[2] * rhs[0]) - (lhs[0] * rhs[2]), (lhs[0] * rhs[1]) - (lhs[1] * rhs[0])); }
    template<typename T> inline constexpr vec<T, 2> perpendicular_right(const vec<T, 2>& lhs) { return vec<T, 2>(lhs[1], -lhs[0]); }
    template<typename T> inline constexpr vec<T, 2> perpendicular_left(const vec<T, 2>& lhs) { return vec<T, 2>(-lhs[1], lhs[0]); }
} // namespace rnm


#endif // _RENA_MATHEMATICS_DETAIL_VEC_HPP_
