//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/combinatorial.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::gcd", eve::test::simd::integers)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::gcd(T()  , T()  ), T  );
  TTS_EXPR_IS(eve::gcd(T()  , e_t()), T  );
  TTS_EXPR_IS(eve::gcd(e_t(), T()  ), T  );
  TTS_EXPR_IS(eve::gcd(e_t(), e_t()), e_t);
};

auto mini = tts::constant([]<typename T>(eve::as<T> const&)
                          { return eve::inc(eve::valmin(eve::as<T>())); });

TTS_CASE_WITH("Check  behavior of eve::gcd on wide",
              eve::test::simd::integers,
              tts::generate(tts::randoms(mini, eve::valmax), tts::randoms(mini, eve::valmax)))
<typename T>(const T& a0, const T& a1)
{
  using v_t = eve::element_type_t<T>;
  if constexpr(sizeof(v_t) <  8)
  {
    TTS_EQUAL(eve::gcd(a0, a1), tts::map([](auto e, auto f) -> v_t { return std::gcd(e, f); }, a0, a1));
  }
};

//==================================================================================================
//=== Test for peculiars values
//==================================================================================================
TTS_CASE_TPL("Check  behavior of eve::gcd on wide peculiar cases", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::gcd;

  TTS_ULP_EQUAL(gcd(T(10), T(5)), T(5), 0);
  TTS_ULP_EQUAL(gcd(T(6), T(2)), T(2), 0);
  TTS_ULP_EQUAL(gcd(T(36), T(45)), T(9), 0);
  TTS_ULP_EQUAL(gcd(T(1), T(0)), T(1), 0);
  TTS_ULP_EQUAL(gcd(T(0), T(0)), T(0), 0);
  TTS_ULP_EQUAL(gcd(T(0), T(1)), T(1), 0);
};
