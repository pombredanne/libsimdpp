/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_TO_FLOAT64_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_TO_FLOAT64_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/mem_block.h>
#include <simdpp/core/move_l.h>
#include <simdpp/sse/extract_half.h>
#include <simdpp/core/detail/vec_insert.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


inline float64x4 i_to_float64(int32x4 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    detail::mem_block<int32x4> ax(a);
    float64x4 r;
    r.vec(0).el(0) = double(ax[0]);
    r.vec(0).el(1) = double(ax[1]);
    r.vec(1).el(0) = double(ax[2]);
    r.vec(1).el(1) = double(ax[3]);
    return r;
#elif SIMDPP_USE_AVX
    return _mm256_cvtepi32_pd(a);
#elif SIMDPP_USE_SSE2
    float64x2 r1, r2;
    r1 = _mm_cvtepi32_pd(a);
    r2 = _mm_cvtepi32_pd(move4_r<2>(a).eval());
    return combine(r1, r2);
#endif
}

#if SIMDPP_USE_AVX2
inline float64<8> i_to_float64(int32x8 a)
{
#if SIMDPP_USE_AVX512
    return _mm512_cvtepi32_pd(a);
#else
    float64x4 r1, r2;
    int32x4 a1, a2;
    split(a, a1, a2);
    r1 = _mm256_cvtepi32_pd(a1);
    r2 = _mm256_cvtepi32_pd(a2);
    return combine(r1, r2);
#endif
}
#endif

#if SIMDPP_USE_AVX512
inline float64<16> i_to_float64(int32<16> a)
{
    float64<8> r1, r2;
    int32<8> a1, a2;
    split(a, a1, a2);
    r1 = _mm512_cvtepi32_pd(a1);
    r2 = _mm512_cvtepi32_pd(a2);
    return combine(r1, r2);
}
#endif

template<unsigned N>
float64<N> i_to_float64(int32<N> a)
{
    float64<N> r;
    for (unsigned i = 0; i < a.vec_length; ++i) {
        detail::vec_insert(r, i_to_float64(a.vec(i)), i);
    }
    return r;
}

// -----------------------------------------------------------------------------

inline float64x4 i_to_float64(float32x4 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    detail::mem_block<float32x4> ax(a);
    float64x4 r;
    r.vec(0).el(0) = double(ax[0]);
    r.vec(0).el(1) = double(ax[1]);
    r.vec(1).el(0) = double(ax[2]);
    r.vec(1).el(1) = double(ax[3]);
    return r;
#elif SIMDPP_USE_AVX
    return _mm256_cvtps_pd(a);
#elif SIMDPP_USE_SSE2
    float64x2 r1, r2;
    r1 = _mm_cvtps_pd(a);
    r2 = _mm_cvtps_pd(move4_r<2>(a).eval());
    return combine(r1, r2);
#endif
}

#if SIMDPP_USE_AVX
inline float64<8> i_to_float64(float32x8 a)
{
#if SIMDPP_USE_AVX512
    return _mm512_cvtps_pd(a);
#else
    float64x4 r1, r2;
    float32x4 a1, a2;
    split(a, a1, a2);
    r1 = _mm256_cvtps_pd(a1);
    r2 = _mm256_cvtps_pd(a2);
    return combine(r1, r2);
#endif
}
#endif

#if SIMDPP_USE_AVX512
inline float64<16> i_to_float64(float32<16> a)
{
    float64<8> r1, r2;
    float32<8> a1, a2;
    split(a, a1, a2);
    r1 = _mm512_cvtps_pd(a1);
    r2 = _mm512_cvtps_pd(a2);
    return combine(r1, r2);
}
#endif

template<unsigned N>
float64<N> i_to_float64(float32<N> a)
{
    float64<N> r;
    for (unsigned i = 0; i < a.vec_length; ++i) {
        detail::vec_insert(r, i_to_float64(a.vec(i)), i);
    }
    return r;
}


} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

