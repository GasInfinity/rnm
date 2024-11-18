#ifndef _RENA_MATHEMATICS_DETAIL_BASE_HPP_
#define _RENA_MATHEMATICS_DETAIL_BASE_HPP_

#if defined(__GNUC__)
    #define rnm_forceinline [[gnu::always_inline]] inline
#elif defined(_MSC_VER)
    #define rnm_forceinline __forceinline
#else
    #define rnm_forceinline inline
#endif

#endif // _RENA_MATHEMATICS_DETAIL_BASE_HPP_
