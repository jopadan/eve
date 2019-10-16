//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_X86_MAKE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_X86_MAKE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/compiler.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>

#if defined(EVE_COMP_IS_GNUC)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits make
  template<typename T, typename... Vs, typename = arithmetic<T>>
  EVE_FORCEINLINE auto make(as_<T> const &, eve::sse_ const &, Vs... vs) noexcept
  {
    static_assert(sizeof...(Vs) <= limits<eve::sse2_>::bytes / sizeof(T),
                  "[eve::make sse] - Invalid number of arguments");

    if constexpr(std::is_same_v<T, double>) { return _mm_setr_pd(static_cast<double>(vs)...); }
    else if constexpr(std::is_same_v<T, float>)
    {
      if constexpr(sizeof...(vs) == 4) return _mm_setr_ps(static_cast<float>(vs)...);
      if constexpr(sizeof...(vs) == 2) return _mm_setr_ps(static_cast<float>(vs)..., 0.f, 0.f);
    }
    else
    {
      if(sizeof(T) == 8)
      {
        __m128i that;
        T *     ptr = reinterpret_cast<detail::alias_t<T> *>(&that);
        T       d[] = {static_cast<T>(vs)...};
        ptr[ 0 ]    = d[ 0 ];
        ptr[ 1 ]    = d[ 1 ];
        detail::ignore(that);
        return that;
      }

      if constexpr(sizeof...(vs) == 4 && sizeof(T) == 4)
        return _mm_setr_epi32(static_cast<int>(vs)...);
      if constexpr(sizeof...(vs) == 2 && sizeof(T) == 4)
        return _mm_setr_epi32(static_cast<int>(vs)..., 0, 0);

      if constexpr(sizeof...(vs) == 8 && sizeof(T) == 2)
        return _mm_setr_epi16(static_cast<short>(vs)...);
      if constexpr(sizeof...(vs) == 4 && sizeof(T) == 2)
        return _mm_setr_epi16(static_cast<short>(vs)..., 0, 0, 0, 0);
      if constexpr(sizeof...(vs) == 2 && sizeof(T) == 2)
        return _mm_setr_epi16(static_cast<short>(vs)..., 0, 0, 0, 0, 0, 0);

      if constexpr(sizeof...(vs) == 16 && sizeof(T) == 1)
        return _mm_setr_epi8(static_cast<char>(vs)...);
      if constexpr(sizeof...(vs) == 8 && sizeof(T) == 1)
        return _mm_setr_epi8(static_cast<char>(vs)..., 0, 0, 0, 0, 0, 0, 0, 0);
      if constexpr(sizeof...(vs) == 4 && sizeof(T) == 1)
        return _mm_setr_epi8(static_cast<char>(vs)..., 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
      if constexpr(sizeof...(vs) == 2 && sizeof(T) == 1)
        return _mm_setr_epi8(static_cast<char>(vs)..., 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    }
  }

  template<typename T, typename V, typename = arithmetic<T>>
  EVE_FORCEINLINE auto make(as_<T> const &, eve::sse_ const &, V v) noexcept
  {
    if constexpr(std::is_same_v<T, double>) { return _mm_set1_pd(static_cast<double>(v)); }
    else if constexpr(std::is_same_v<T, float>)
    {
      return _mm_set1_ps(static_cast<float>(v));
    }
    else
    {
      if(sizeof(T) == 8)
      {
        __m128i that;
        T *     ptr = reinterpret_cast<detail::alias_t<T> *>(&that);
        ptr[ 0 ] = ptr[ 1 ] = static_cast<T>(v);
        detail::ignore(that);
        return that;
      }
      if(sizeof(T) == 4) return _mm_set1_epi32(static_cast<int>(v));
      if(sizeof(T) == 2) return _mm_set1_epi16(static_cast<short>(v));
      if(sizeof(T) == 1) return _mm_set1_epi8(static_cast<char>(v));
    }
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits make
  template<typename T, typename... Vs, typename = arithmetic<T>>
  EVE_FORCEINLINE auto make(as_<T> const &, eve::avx_ const &, Vs... vs) noexcept
  {
    static_assert(sizeof...(Vs) <= limits<eve::avx_>::bytes / sizeof(T),
                  "[eve::make sse] - Invalid number of arguments");

    if constexpr(std::is_same_v<T, double>) { return _mm256_setr_pd(vs...); }
    else if constexpr(std::is_same_v<T, float>)
    {
      return _mm256_setr_ps(vs...);
    }
    else
    {
      if constexpr(sizeof...(vs) == 4 && sizeof(T) == 8) return _mm256_setr_epi64x(vs...);
      if constexpr(sizeof...(vs) == 8 && sizeof(T) == 4) return _mm256_setr_epi32(vs...);
      if constexpr(sizeof...(vs) == 16 && sizeof(T) == 2) return _mm256_setr_epi16(vs...);
      if constexpr(sizeof...(vs) == 32 && sizeof(T) == 1) return _mm256_setr_epi8(vs...);
    }
  }

  template<typename T, typename V, typename = arithmetic<T>>
  EVE_FORCEINLINE auto make(as_<T> const &, eve::avx_ const &, V v) noexcept
  {
    if constexpr(std::is_same_v<T, double>) { return _mm256_set1_pd(v); }
    else if constexpr(std::is_same_v<T, float>)
    {
      return _mm256_set1_ps(v);
    }
    else
    {
      if(sizeof(T) == 8) return _mm256_set1_epi64x(v);
      if(sizeof(T) == 4) return _mm256_set1_epi32(v);
      if(sizeof(T) == 2) return _mm256_set1_epi16(v);
      if(sizeof(T) == 1) return _mm256_set1_epi8(v);
    }
  }

  //------------------------------------------------------------------------------------------------
  // logical cases
  template<typename T, typename... Vs>
  EVE_FORCEINLINE auto make(as_<logical<T>> const &, eve::sse_ const &, Vs... vs) noexcept
  {
    return make(as_<T>{}, eve::sse_{}, logical<T>(vs).mask()...);
  }

  template<typename T, typename... Vs>
  EVE_FORCEINLINE auto make(as_<logical<T>> const &, eve::avx_ const &, Vs... vs) noexcept
  {
    return make(as_<T>{}, eve::avx_{}, logical<T>(vs).mask()...);
  }
}

#if defined(EVE_COMP_IS_GNUC)
#  pragma GCC diagnostic pop
#endif

#endif
