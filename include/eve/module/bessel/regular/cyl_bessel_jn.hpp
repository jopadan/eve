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
  struct cyl_bessel_jn_t : elementwise_callable<cyl_bessel_jn_t, Options>
  {
    template<eve::ordered_value N, eve::floating_ordered_value T>
    as_wide_as_t<T, N> operator()(N n, T x) const  { return EVE_DISPATCH_CALL(n, x); }

    EVE_CALLABLE_OBJECT(cyl_bessel_jn_t, cyl_bessel_jn_);
  };

  //================================================================================================
  //! @addtogroup bessel
  //! @{
  //!   @var cyl_bessel_jn
  //!   @brief Computes the Bessel functions of the first kind,
  //!   \f$ J_{n}(x)=\sum_{p=0}^{\infty}{\frac{(-1)^p}{p!\,\Gamma (p+n +1)}}
  //!   {\left({x \over 2}\right)}^{2p+n }\f$.
  //!
  //!   It is the solution of \f$ x^{2}y''+xy'+(x^2-n^2)y=0\f$ for which
  //!   \f$ y(0) = 0\f$ if \f$n \ne 0\f$ else \f$1\f$.
  //!
  //!   **Defined in header**
  //!
  //!   @code
  //!   #include <eve/module/bessel.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::ordered_value N, eve::floating_ordered_value T >
  //!      T cyl_bessel_jn(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `n`:   order of the function (non necessarily integral)
  //!
  //!     * `x` :  [ordered floating argument](@ref eve::floating_ordered_value).
  //!
  //!   **Return value**
  //!
  //!   The value of \f$\displaystyle J_{n}(x)=\sum_{p=0}^{\infty}{\frac{(-1)^p}{p!\,\Gamma (p+n +1)}}
  //!   {\left({x \over 2}\right)}^{2p+n }\f$ is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/bessel/regular/cyl_bessel_jn.cpp}
  //! @}
  //================================================================================================
 inline constexpr auto cyl_bessel_jn = functor<cyl_bessel_jn_t>;
}


#include <eve/module/bessel/regular/impl/cyl_bessel_jn.hpp>
