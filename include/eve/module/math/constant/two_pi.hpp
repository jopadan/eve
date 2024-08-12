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
struct two_pi_t : constant_callable<two_pi_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward))        return T(0x1.921fb6p+2);
      else if constexpr(Opts::contains(downward)) return T(0x1.921fb4p+2);
      else                                         return T(0x1.921fb6p+2);
    }
    else
    {
      if constexpr(Opts::contains(upward))        return T(0x1.921fb54442d19p+2);
      else if constexpr(Opts::contains(downward)) return T(0x1.921fb54442d18p+2);
      else                                         return T(0x1.921fb54442d18p+2);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(two_pi_t, two_pi_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var two_pi
//!   @brief Callable object computing the constant \f$2\pi\f$.
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
//!      T two_pi(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::two_pi(as<T>())` returns \f$2\pi\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/two_pi.cpp}
//! @}
//================================================================================================
inline constexpr auto two_pi = functor<two_pi_t>;
}
