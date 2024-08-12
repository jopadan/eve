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

namespace eve
{
template<typename Options>
struct zeta_3_t : constant_callable<zeta_3_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward))        return T(0x1.33ba02p+0);
      else if constexpr(Opts::contains(downward)) return T(0x1.33bap+0);
      else                                         return T(0x1.33bap+0);
    }
    else
    {
      if constexpr(Opts::contains(upward))        return T(0x1.33ba004f00622p+0);
      else if constexpr(Opts::contains(downward)) return T(0x1.33ba004f00621p+0);
      else                                         return T(0x1.33ba004f00621p+0);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(zeta_3_t, zeta_3_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var zeta_3
//!   @brief Callable object computing the constant \f$\zeta(3)\f$.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::value T >
//!      T zeta_3(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::zeta_3(as<T>())` returns  \f$\zeta(3)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/zeta_3.cpp}
//! @}
//================================================================================================
inline constexpr auto zeta_3 = functor<zeta_3_t>;
}
