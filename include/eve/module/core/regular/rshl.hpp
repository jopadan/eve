//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/detail/assert_utils.hpp>

namespace eve
{
  template<typename Options>
  struct rshl_t : strict_elementwise_callable<rshl_t, Options>
  {
    template<unsigned_value T, integral_value N>
    requires(eve::same_lanes_or_scalar<T, N>)
    EVE_FORCEINLINE constexpr as_wide_as_t<T, N> operator()(T t0, N s) const noexcept
    {
      EVE_ASSERT(detail::assert_good_shift<T>(s),
                 "[eve::rshl] - Shifting by " << s << " is out of the range ]"
                 << -int(sizeof(element_type_t<T>) * 8) << ", "
                 << sizeof(element_type_t<T>) * 8 << "[.");
      return EVE_DISPATCH_CALL(t0, s);
    }

    template<unsigned_value T, std::ptrdiff_t S>
    EVE_FORCEINLINE constexpr T operator()(T t0, index_t<S> s) const noexcept
    {
      EVE_ASSERT(detail::assert_good_shift<T>(S),
                 "[eve::rshl] - Shifting by " << S << " is out of the range ]"
                 << -int(sizeof(element_type_t<T>) * 8) << ", "
                 << sizeof(element_type_t<T>) * 8 << "[.");
      return EVE_DISPATCH_CALL(t0, s);
    }

    EVE_CALLABLE_OBJECT(rshl_t, rshl_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var rshl
//!   @brief Computes the arithmetic left/right shift operation according to shift sign.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::unsigned_value T , integral_value N >
//!      T rshl(T x, N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value) to be shifted.
//!     * `n`:   [shift](@ref eve::integral_value).
//!
//!    **Return value**
//!
//!      The value of the arithmetic left/right shift operation according to shift
//!      sign is returned
//!
//!   @note
//!     *  the call `rshl(x, n)` is equivalent to `if_else(n>0, shl(x, n), shr(x, n))`
//!        if `x`  is an  [simd value](@ref eve::simd_value).
//!
//!     *  The types must share the same cardinal or be scalar and if `N`
//!        is the size in bits  of the element type of `T`, all
//!        [elements](@ref glossary_elementwise) of n must belong to the
//!        interval: `]-N, N[` or the result is undefined.
//!
//!     * The call `rshl(x, n)` is equivalent to `x << n` if `x`  is
//!       an [simd value](@ref eve::simd_value).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/rshl.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::rshl[mask](x, ...)` provides a masked
//!     version of `rshl` which is
//!     equivalent to `if_else(mask, rshl(x, ...), x)`
//!
//! @}
//================================================================================================
  inline constexpr auto rshl = functor<rshl_t>;
}

#include <eve/module/core/regular/impl/rshl.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/rshl.hpp>
#endif
