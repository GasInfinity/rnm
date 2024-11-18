#ifndef _RENA_MATHEMATICS_DETAIL_MAT_HPP_
#define _RENA_MATHEMATICS_DETAIL_MAT_HPP_

#include "base.hpp"
#include "common.hpp"

#include "vec.hpp"

#include <type_traits>
#include <cstddef>
#include <utility>

namespace rnm
{
    template<typename T, std::size_t R, std::size_t C> requires (R != 0 && C != 0)
    struct mat
    {
        using scalar = T;
        constexpr static std::size_t data_size = R * C;

        T data[data_size];

        constexpr mat() : data() { }
        constexpr explicit mat(T _scalar) : mat(_scalar, std::make_index_sequence<data_size>{}) { }
        constexpr explicit mat(const T* _data) : mat(_data, std::make_index_sequence<data_size>{}) { }
        template<typename... U> constexpr mat(U... _args) requires (sizeof...(_args) == data_size && (std::is_convertible_v<U, T> && ...)) : data{static_cast<T>(_args)...} { }
        template<typename... X> constexpr mat(const vec<X, C>&... _args) requires (sizeof...(_args) == R && (std::is_convertible_v<X, T> && ...)) : mat(std::make_index_sequence<R*C>{}, _args...) { }
        template<typename... X> constexpr mat(const X(&... _args)[C]) requires (sizeof...(_args) == R && (std::is_convertible_v<X, T> && ...)) : mat(std::make_index_sequence<R*C>{}, _args...) { }

        rnm_forceinline constexpr T& operator[](std::size_t n) { return data[n]; }
        rnm_forceinline constexpr const T& operator[](std::size_t n) const { return data[n]; }

        rnm_forceinline constexpr T& operator[](std::size_t r, std::size_t c) { return data[r*C + c]; }
        rnm_forceinline constexpr const T& operator[](std::size_t r, std::size_t c) const { return data[r*C + c]; }

        template<typename U> constexpr explicit operator mat<U, R, C>() const { return cast_helper(std::make_index_sequence<data_size>{}); }
        
        constexpr static mat<T, R, C> identity() requires (R == C)
        { return identity(std::make_index_sequence<data_size>{}); }
    private:
        template<std::size_t... I> rnm_forceinline constexpr explicit mat(T _scalar, const std::index_sequence<I...>&) : data{((void)I, _scalar)...} { }
        template<std::size_t... I> rnm_forceinline constexpr explicit mat(const T* _data, const std::index_sequence<I...>&) : data{(_data[I])...} { }
        template<typename... U, std::size_t... I> rnm_forceinline constexpr explicit mat(const std::index_sequence<I...>&, const U&... _args) : data{static_cast<T>((_args...[I / C])[I % C])...} { }

        template<typename U, std::size_t... I> constexpr mat<U, R, C> cast_helper(const std::index_sequence<I...>&) const { return mat<U, R, C>(static_cast<U>(data[I])...); }

        template<std::size_t... I> rnm_forceinline constexpr static mat<T, R, C> identity(const std::index_sequence<I...>&) requires (R == C)
        { return mat<T, R, C>(static_cast<T>(I % R == I / C)...); }
    };

    namespace detail
    {
        // This is the most overengineered matrix multiplication :skull:
        template<typename T, std::size_t CR, std::size_t R, std::size_t O, std::size_t... I>
        rnm_forceinline constexpr vec<T, CR> mat_lhs_vec_helper(const mat<T, R, CR>& lhs, const std::index_sequence<I...>&)
        { return vec<T, CR>(lhs[O, I]...); }

        template<typename T, std::size_t CR, std::size_t C, std::size_t O, std::size_t... I>
        rnm_forceinline constexpr vec<T, CR> mat_rhs_vec_helper(const mat<T, CR, C>& rhs, const std::index_sequence<I...>&)
        { return vec<T, CR>(rhs[I, O]...); }

        template<typename T, std::size_t CR, std::size_t R, std::size_t C, std::size_t... I>
        rnm_forceinline constexpr mat<T, R, C> mat_mul_helper(const mat<T, R, CR>& lhs, const mat<T, CR, C>& rhs, const std::index_sequence<I...>&)
        { return mat<T, R, C>(dot_helper(mat_lhs_vec_helper<T, CR, R, (I / C)>(lhs, std::make_index_sequence<CR>{}), mat_rhs_vec_helper<T, CR, C, (I % C)>(rhs, std::make_index_sequence<CR>{}), std::make_index_sequence<CR>{})...); }
    }

    template<typename T, std::size_t R, std::size_t C> inline constexpr mat<T, R, C>& operator+=(mat<T, R, C>& lhs, const mat<T, R, C>& rhs) { return detail::addr_helper(lhs, rhs, std::make_index_sequence<R*C>{}); }
    template<typename T, std::size_t R, std::size_t C> inline constexpr mat<T, R, C>& operator-=(mat<T, R, C>& lhs, const mat<T, R, C>& rhs) { return detail::subr_helper(lhs, rhs, std::make_index_sequence<R*C>{}); }
    template<typename T, std::size_t R, std::size_t C> inline constexpr mat<T, R, C>& operator*=(mat<T, R, C>& lhs, T rhs) { return detail::mulr_helper(lhs, rhs, std::make_index_sequence<R*C>{}); }
    template<typename T, std::size_t R, std::size_t C> inline constexpr mat<T, R, C>& operator/=(mat<T, R, C>& lhs, T rhs) { return detail::divr_helper(lhs, rhs, std::make_index_sequence<R*C>{}); }

    template<typename T, std::size_t R, std::size_t C> inline constexpr mat<T, R, C> operator -(const mat<T, R, C>& lhs) { return detail::neg_helper(lhs, std::make_index_sequence<R*C>{}); }
    template<typename T, std::size_t R, std::size_t C> inline constexpr mat<T, R, C> operator +(const mat<T, R, C>& lhs, const mat<T, R, C>& rhs) { return detail::add_helper(lhs, rhs, std::make_index_sequence<R*C>{}); }
    template<typename T, std::size_t R, std::size_t C> inline constexpr mat<T, R, C> operator -(const mat<T, R, C>& lhs, const mat<T, R, C>& rhs) { return detail::sub_helper(lhs, rhs, std::make_index_sequence<R*C>{}); }
    template<typename T, std::size_t R, std::size_t C> inline constexpr mat<T, R, C> operator *(const mat<T, R, C>& lhs, T rhs) { return detail::mul_helper(lhs, rhs, std::make_index_sequence<R*C>{}); }
    template<typename T, std::size_t R, std::size_t C> inline constexpr mat<T, R, C> operator *(T lhs, const mat<T, R, C>& rhs) { return detail::mul_helper(rhs, lhs, std::make_index_sequence<R*C>{}); }
    template<typename T, std::size_t R, std::size_t C> inline constexpr mat<T, R, C> operator /(const mat<T, R, C>& lhs, T rhs) { return detail::div_helper(lhs, rhs, std::make_index_sequence<R*C>{}); }

    template<typename T, std::size_t CR, std::size_t R, std::size_t C> inline constexpr mat<T, R, C> operator *(const mat<T, R, CR>& lhs, const mat<T, CR, C>& rhs) { return detail::mat_mul_helper(lhs, rhs, std::make_index_sequence<R*C>{}); }

    template<typename T, std::size_t N> inline constexpr mat<T, N, 1> vec_castr(const vec<T, N>& lhs)
    { return detail::cast_compound_to_compound_helper<mat<T, N, 1>, vec<T, N>>(lhs, std::make_index_sequence<N>{}); }
    
    template<typename T, std::size_t N> inline constexpr mat<T, 1, N> vec_castc(const vec<T, N>& lhs)
    { return detail::cast_compound_to_compound_helper<mat<T, 1, N>, vec<T, N>>(lhs, std::make_index_sequence<N>{}); }

    template<typename T, std::size_t N> inline constexpr vec<T, N> mat_cast(const mat<T, N, 1>& lhs)
    { return detail::cast_compound_to_compound_helper<vec<T, N>, mat<T, N, 1>>(lhs, std::make_index_sequence<N>{}); }
    
    template<typename T, std::size_t N> inline constexpr vec<T, N> mat_cast(const mat<T, 1, N>& lhs)
    { return detail::cast_compound_to_compound_helper<vec<T, N>, mat<T, 1, N>>(lhs, std::make_index_sequence<N>{}); }

    template<typename T, std::size_t N, std::size_t R> inline constexpr vec<T, N> operator*(const mat<T, R, N>& lhs, const vec<T, N>& rhs)
    { return mat_cast(lhs * vec_castr(rhs)); }
    
    template<typename T, std::size_t N, std::size_t C> inline constexpr vec<T, N> operator*(const vec<T, N>& lhs, const mat<T, N, C>& rhs)
    { return mat_cast(vec_castc(lhs) * rhs); }
} // namespace rnm

#endif // _RENA_MATHEMATICS_DETAIL_MAT_HPP_
