#ifndef _RENA_MATHEMATICS_DETAIL_MAT_TRANSFORMATIONS_HPP_
#define _RENA_MATHEMATICS_DETAIL_MAT_TRANSFORMATIONS_HPP_

#include "base.hpp"
#include "common.hpp"

#include "mat.hpp"

#include <utility>
#include <cstddef>
#include <cmath>

namespace rnm
{
    namespace detail
    {
        template<typename T, std::size_t N, std::size_t M, std::size_t... I>
        rnm_forceinline constexpr mat<T, M, M> translation_helper(const vec<T, N>& translation, const std::index_sequence<I...>&)
        { return mat<T, M, M>((((I % M) == N && (I / M) != N) ? translation[(I / M)] : static_cast<T>((I / M) == (I % M)))...); }

        template<typename T, std::size_t N, std::size_t M, std::size_t... I>
        rnm_forceinline constexpr mat<T, M, M> scale_helper(const vec<T, N>& scale, const std::index_sequence<I...>&)
        { return mat<T, M, M>(((I % M) == (I / M) && (I / M) != N ? scale[(I / M)] : static_cast<T>((I / M) == (I % M)))...); }
    } // namespace detail

    /* Translation / Rotation / Scale */
    template<typename T, std::size_t N> inline constexpr mat<T, N+1, N+1> translate(const vec<T, N>& translation) { return detail::translation_helper<T, N, N+1>(translation, std::make_index_sequence<(N+1)*(N+1)>{}); }
    template<typename T, std::size_t N> inline constexpr mat<T, N+1, N+1> scale(const vec<T, N>& scale) { return detail::scale_helper<T, N, N+1>(scale, std::make_index_sequence<(N+1)*(N+1)>{}); }
    template<typename T> inline constexpr mat<T, 3, 3> shear(const vec<T, 2>& shear) { return mat<T, 3, 3>(1 + shear.x * shear.y, shear.x, 0, shear.y, 1, 0, 0, 0, 1); }

    template<typename T> inline constexpr mat<T, 3, 3> rotate(T rotation)
    {
        const T sin = std::sin(rotation);
        const T cos = std::cos(rotation);
        
        return mat<T, 3, 3>(cos, -sin, 0, 
                            sin, cos,  0, 
                            0,   0,    1);
    }

    template<typename T, std::size_t N> inline constexpr mat<T, N, N> scale_linear(const vec<T, N>& scale)
    { return detail::scale_helper<T, N, N>(scale, std::make_index_sequence<N*N>{}); }

    template<typename T> inline constexpr mat<T, 2, 2> shear_linear(const vec<T, 2>& shear)
    { return mat<T, 2, 2>(1 + shear.x * shear.y, shear.x, shear.y, 1); }

    template<typename T> inline constexpr mat<T, 2, 2> rotate_linear(T rotation)
    {
        const T sin = std::sin(rotation);
        const T cos = std::cos(rotation);
        
        return mat<T, 2, 2>(cos, -sin,
                            sin,  cos);
    }

    /* Projections 
     * When multiplied, the homogeneous vector result will be in the range -1 .. 1 for x and y, and 0 .. 1 for z
     * Assuming -1 -> top left in the y coordinate
     * a.k.a: D3D and VK. OGL will need GL_ARB_clip_control or an extra transformation
     * */
    template<typename T> inline constexpr mat<T, 3, 3> ortho(T left, T right, T bottom, T top)
    {
        const T w = right - left;
        const T h = top - bottom;
        return mat<T, 3, 3>(2 / w, 0, -((right + left) / w), 0, 2 / h, -((top + bottom) / h), 0, 0, 1);
    }

    template<typename T> inline constexpr mat<T, 4, 4> ortho(T left, T right, T bottom, T top, T near, T far)
    {
        const T w = right - left;
        const T h = top - bottom;
        const T d = far - near;
        return mat<T, 4, 4>(2 / w, 0, 0, -((right + left) / w), 0, 2 / h, 0, -((top + bottom) / h), 0, 0, 1 / d, -near / d, 0, 0, 0, 1);
    }

    template<typename T> inline constexpr mat<T, 4, 4> perspective(T vfov, T aspect, T near, T far)
    {
        const T half_vfov_tan = std::tan(vfov / static_cast<T>(2));
        const T d = far - near;
        return mat<T, 4, 4>(1 / (aspect * half_vfov_tan), 0, 0, 0, 0, 1 / half_vfov_tan, 0, 0, 0, 0, (near + far) / d, -(near * far) / d, 0, 0, 1, 0);
    }
}

#endif // _RENA_MATHEMATICS_DETAIL_MAT_TRANSFORMATIONS_HPP_
