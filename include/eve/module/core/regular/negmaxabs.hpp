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
  struct negmaxabs_t : tuple_callable<negmaxabs_t, Options, numeric_option, pedantic_option, saturated_option>
  {
    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr  kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup t) const noexcept  requires(kumi::size_v<Tup> >= 2) { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(negmaxabs_t, negmaxabs_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var negmaxabs
//!   @brief `tuple_callable` object computing the negated value of the element of maximal absolute value.
//!
//!   @groupheader{Header file}
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
//!      // Regular overloads
//!      constexpr auto negmaxabs(eve::value auto x, eve::value auto ... xs)                 noexcept; // 1
//!      constexpr auto negmaxabs(kumi::non_empty_product_type auto const& tup)              noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto negmaxabs[conditional_expr auto c](/* any of the above overloads */) noexcept; // 3
//!      constexpr auto negmaxabs[logical_value auto m](/* any of the above overloads */)    noexcept; // 3
//!
//!      // Semantic option
//!      constexpr auto negmaxabs[saturated](/* any of the above overloads */)               noexcept; // 4
//!
//!      // Exclusive Semantic options - Only one of those can be set at once
//!      constexpr auto negmaxabs[pedantic](/* any of the above overloads */)                noexcept; // 5.1
//!      constexpr auto negmaxabs[numeric ](/* any of the above overloads */)                noexcept; // 5.2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,  `...xs`: [arguments](@ref eve::value).
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      The negated value of the element of maximal absolute value is returned.
//!        1. If any element of the inputs is a NaN the corresponding output element is system-dependent
//!        2. equivalent to the call on the elements of the tuple.
//!        3. [The operation is performed conditionnaly](@ref conditional)
//!        4. computation internally uses `abs[saturated]` instead of `abs`
//!        5. with `numeric` (resp. `pedantic`) `max[numeric]` (5.1) (resp. `max[pedantic]` (5.2))
//!           is used internally
//!  @groupheader{Example}
//!  @godbolt{doc/core/negmaxabs.cpp}
//================================================================================================
  inline constexpr auto negmaxabs = functor<negmaxabs_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/negmaxabs.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/negmaxabs.hpp>
#endif
