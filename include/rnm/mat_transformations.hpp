#ifndef _RENA_MATHEMATICS_MAT_TRANSFORMATIONS_HPP_
#define _RENA_MATHEMATICS_MAT_TRANSFORMATIONS_HPP_

#include "vec.hpp"
#include "mat.hpp"

#include <cstddef>

namespace rnm
{
    template<typename T, std::size_t N> inline constexpr mat<T, N+1, N+1> translate(const vec<T, N>& translation);
    template<typename T, std::size_t N> inline constexpr mat<T, N+1, N+1> scale(const vec<T, N>& scale);
    template<typename T> inline constexpr mat<T, 3, 3> shear(const vec<T, 2>& shear);
    template<typename T> inline constexpr mat<T, 3, 3> rotate(T rotation);

    template<typename T, std::size_t N> inline constexpr mat<T, N, N> scale_linear(const vec<T, N>& scale);
    template<typename T> inline constexpr mat<T, 2, 2> shear_linear(const vec<T, 2>& shear);
    template<typename T> inline constexpr mat<T, 2, 2> rotate_linear(T rotation);

    /* Projections 
     * When multiplied, the homogeneous vector result will be in the range -1 .. 1 for x and y, and 0 .. 1 for z
     * Assuming -1 -> top left in the y coordinate
     * a.k.a: D3D and VK. OGL will need GL_ARB_clip_control or an extra transformation
     * */
    template<typename T> inline constexpr mat<T, 3, 3> ortho(T left, T right, T bottom, T top);
    template<typename T> inline constexpr mat<T, 4, 4> ortho(T left, T right, T bottom, T top, T near, T far);
    template<typename T> inline constexpr mat<T, 4, 4> perspective(T vfov, T aspect, T near, T far);
}

#include "detail/mat_transformations.hpp"

#endif // _RENA_MATHEMATICS_MAT_TRANSFORMATIONS_HPP_
