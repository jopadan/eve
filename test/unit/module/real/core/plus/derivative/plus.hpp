//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/derivative/plus.hpp>
#include <type_traits>

TTS_CASE_TPL("Check derivative(plus) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using ui_t = eve::detail::as_integer_t<T, unsigned>;
    TTS_EXPR_IS(eve::derivative(eve::plus)(T(), unsigned()), T);
    TTS_EXPR_IS(eve::derivative(eve::plus)(T(), ui_t()), T);
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::plus) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::derivative(eve::plus)(T{10}, 0u), T(10));
    TTS_EQUAL(eve::derivative(eve::plus)(T{10}, 1u), T(1));
    TTS_EQUAL(eve::derivative(eve::plus)(T{10}, 2u), T(0));
    TTS_EQUAL(eve::derivative(eve::plus)(T{-10}, 0u), T(-10));
    TTS_EQUAL(eve::derivative(eve::plus)(T{-10}, 1u), T(1));
    TTS_EQUAL(eve::derivative(eve::plus)(T{-10}, 2u), T(0));
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}
