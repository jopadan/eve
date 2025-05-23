//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/if_else.hpp>

#include <type_traits>

namespace eve::detail
{
  template<eve::simd_value Wide>
  EVE_FORCEINLINE Wide
  if_else_min(Wide x, Wide y)
  {
    return eve::if_else(x > y, y, x);
  }

  template<arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> min_(EVE_REQUIRES(sse2_), O const& opts, wide<T, N> v0, wide<T, N> v1) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(numeric) || O::contains(pedantic))
    {
      return min.behavior(cpu_{}, opts, v0, v1);
    }
    else
    {
      constexpr auto c = categorize<wide<T, N>>();

      // 512
      if constexpr( c == category::float64x8 ) return _mm512_min_pd(v0, v1);
      else if constexpr( c == category::float32x16 ) return _mm512_min_ps(v0, v1);
      else if constexpr( c == category::int64x8 ) return _mm512_min_epi64(v0, v1);
      else if constexpr( c == category::uint64x8 ) return _mm512_min_epu64(v0, v1);
      else if constexpr( c == category::int32x16 ) return _mm512_min_epi32(v0, v1);
      else if constexpr( c == category::uint32x16 ) return _mm512_min_epu32(v0, v1);
      else if constexpr( c == category::int16x32 ) return _mm512_min_epi16(v0, v1);
      else if constexpr( c == category::uint16x32 ) return _mm512_min_epu16(v0, v1);
      else if constexpr( c == category::int8x64 ) return _mm512_min_epi8(v0, v1);
      else if constexpr( c == category::uint8x64 ) return _mm512_min_epu8(v0, v1);

      // 256
      else if constexpr( c == category::float64x4 ) return _mm256_min_pd(v0, v1);
      else if constexpr( c == category::float32x8 ) return _mm256_min_ps(v0, v1);
      // 256 - 64 bit ints
      else if constexpr( current_api >= avx512 && c == category::int64x4 )
        return _mm256_min_epi64(v0, v1);
      else if constexpr( current_api >= avx512 && c == category::uint64x4 )
        return _mm256_min_epu64(v0, v1);
      else if constexpr( match(c, category::int64x4, category::uint64x4) )
        return detail::if_else_min(v0, v1);
      // 256 - 32 bit ints
      else if constexpr( current_api >= avx2 && c == category::int32x8 )
        return _mm256_min_epi32(v0, v1);
      else if constexpr( current_api >= avx2 && c == category::uint32x8 )
        return _mm256_min_epu32(v0, v1);
      else if constexpr( match(c, category::int32x8, category::uint32x8) )
        return aggregate(min, v0, v1);
      // 256 - 16 bit ints
      else if constexpr( current_api >= avx2 && c == category::int16x16 )
        return _mm256_min_epi16(v0, v1);
      else if constexpr( current_api >= avx2 && c == category::uint16x16 )
        return _mm256_min_epu16(v0, v1);
      else if constexpr( match(c, category::int16x16, category::uint16x16) )
        return aggregate(eve::min, v0, v1);
      // 256 - 8 bit ints
      else if constexpr( current_api >= avx2 && c == category::int8x32 ) return _mm256_min_epi8(v0, v1);
      else if constexpr( current_api >= avx2 && c == category::uint8x32 )
        return _mm256_min_epu8(v0, v1);
      else if constexpr( match(c, category::int8x32, category::uint8x32) )
        return aggregate(eve::min, v0, v1);

      // 128
      else if constexpr( c == category::float64x2 ) return _mm_min_pd(v0, v1);
      else if constexpr( c == category::float32x4 ) return _mm_min_ps(v0, v1);
      // 128 - 64 bit ints
      else if constexpr( current_api >= avx512 && c == category::int64x2 ) return _mm_min_epi64(v0, v1);
      else if constexpr( current_api >= avx512 && c == category::uint64x2 )
        return _mm_min_epu64(v0, v1);
      else if constexpr( current_api >= sse4_2 && c == category::int64x2 )
        return detail::if_else_min(v0, v1);
      else if constexpr( current_api >= sse4_2 && c == category::uint64x2 )
        return detail::if_else_min(v0, v1);
      else if constexpr( match(c, category::int64x2, category::uint64x2) ) return map(min, v0, v1);
      // 128 - 32 bit ints
      else if constexpr( current_api >= sse4_1 && c == category::int32x4 ) return _mm_min_epi32(v0, v1);
      else if constexpr( current_api >= sse4_1 && c == category::uint32x4 )
        return _mm_min_epu32(v0, v1);
      else if constexpr( match(c, category::int32x4, category::uint32x4) )
        return detail::if_else_min(v0, v1);
      // 128 - 16 bit ints
      else if constexpr( c == category::int16x8 ) return _mm_min_epi16(v0, v1);
      else if constexpr( current_api >= sse4_1 && c == category::uint16x8 )
        return _mm_min_epu16(v0, v1);
      else if constexpr( c == category::uint16x8 ) return detail::if_else_min(v0, v1);
      // 128 - 8 bit ints
      else if constexpr( current_api >= sse4_1 && c == category::int8x16 ) return _mm_min_epi8(v0, v1);
      else if constexpr( c == category::int8x16 ) return detail::if_else_min(v0, v1);
      else if constexpr( c == category::uint8x16 ) return _mm_min_epu8(v0, v1);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> min_(EVE_REQUIRES(avx512_), C const& cx, O const& opts, wide<T, N> const& v, wide<T, N> const& w) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(numeric) || O::contains(pedantic))
    {
      return min[opts][cx].retarget(cpu_{}, v, w);
    }
    else
    {
      constexpr auto c    = categorize<wide<T, N>>();
      auto           src  = alternative(cx, v, as<wide<T, N>> {});
      auto           m    = expand_mask(cx, as<wide<T, N>> {}).storage().value;

      if      constexpr( c == category::float32x16) return _mm512_mask_min_ps    (src, m, v, w);
      else if constexpr( c == category::float32x8 ) return _mm256_mask_min_ps    (src, m, v, w);
      else if constexpr( c == category::float32x4 ) return _mm_mask_min_ps       (src, m, v, w);

      else if constexpr( c == category::float64x8 ) return _mm512_mask_min_pd    (src, m, v, w);
      else if constexpr( c == category::float64x4 ) return _mm256_mask_min_pd    (src, m, v, w);
      else if constexpr( c == category::float64x2 ) return _mm_mask_min_pd       (src, m, v, w);

      else if constexpr( c == category::int8x64   ) return _mm512_mask_min_epi8  (src, m, v, w);
      else if constexpr( c == category::int8x32   ) return _mm256_mask_min_epi8  (src, m, v, w);
      else if constexpr( c == category::int8x16   ) return _mm_mask_min_epi8     (src, m, v, w);

      else if constexpr( c == category::int16x32  ) return _mm512_mask_min_epi16 (src, m, v, w);
      else if constexpr( c == category::int16x16  ) return _mm256_mask_min_epi16 (src, m, v, w);
      else if constexpr( c == category::int16x8   ) return _mm_mask_min_epi16    (src, m, v, w);

      else if constexpr( c == category::int32x16  ) return _mm512_mask_min_epi32 (src, m, v, w);
      else if constexpr( c == category::int32x8   ) return _mm256_mask_min_epi32 (src, m, v, w);
      else if constexpr( c == category::int32x4   ) return _mm_mask_min_epi32    (src, m, v, w);

      else if constexpr( c == category::int64x8   ) return _mm512_mask_min_epi64 (src, m, v, w);
      else if constexpr( c == category::int64x4   ) return _mm256_mask_min_epi64 (src, m, v, w);
      else if constexpr( c == category::int64x2   ) return _mm_mask_min_epi64    (src, m, v, w);

      else if constexpr( c == category::uint8x64  ) return _mm512_mask_min_epu8  (src, m, v, w);
      else if constexpr( c == category::uint8x32  ) return _mm256_mask_min_epu8  (src, m, v, w);
      else if constexpr( c == category::uint8x16  ) return _mm_mask_min_epu8     (src, m, v, w);

      else if constexpr( c == category::uint16x32 ) return _mm512_mask_min_epu16 (src, m, v, w);
      else if constexpr( c == category::uint16x16 ) return _mm256_mask_min_epu16 (src, m, v, w);
      else if constexpr( c == category::uint16x8  ) return _mm_mask_min_epu16    (src, m, v, w);

      else if constexpr( c == category::uint32x16 ) return _mm512_mask_min_epu32 (src, m, v, w);
      else if constexpr( c == category::uint32x8  ) return _mm256_mask_min_epu32 (src, m, v, w);
      else if constexpr( c == category::uint32x4  ) return _mm_mask_min_epu32    (src, m, v, w);

      else if constexpr( c == category::uint64x8  ) return _mm512_mask_min_epu64 (src, m, v, w);
      else if constexpr( c == category::uint64x4  ) return _mm256_mask_min_epu64 (src, m, v, w);
      else if constexpr( c == category::uint64x2  ) return _mm_mask_min_epu64    (src, m, v, w);

      else return min[opts][cx].retarget(cpu_{}, v, w);
    }
  }
}
