//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/constant.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(pio_4_, pio_4_);

  template<floating_value T>
  EVE_FORCEINLINE auto Pio_4(as_<T> const & = {}) noexcept
  {
    using t_t =  detail::value_type_t<T>;
    if constexpr(std::is_same_v<t_t, float>) return Constant<T,   0X3F490FDB>();
    else if constexpr(std::is_same_v<t_t, double>) return Constant<T,  0X3FE921FB54442D18LL>();
  }

  EVE_MAKE_NAMED_CONSTANT(pio_4_, Pio_4);
}
