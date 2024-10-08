//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>
#include <iomanip>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of phi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::phi(as<T>()), T);
  TTS_EXPR_IS(eve::phi(as<v_t>()), v_t);
};
//==================================================================================================
// phi  tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of phi on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::lower;
  using eve::upper;

  TTS_IEEE_EQUAL(eve::phi(as<T>()), T(1.61803398874989484820458683436563811772030917980575l));
  TTS_EXPECT(eve::all(eve::phi[eve::lower](as<T>()) <= eve::phi(as<T>())));
  TTS_EXPECT(eve::all(eve::phi(as<T>()) <= eve::phi[eve::upper](as<T>())));
  TTS_ULP_EQUAL(eve::phi[eve::lower](as<T>()), eve::phi[eve::upper](as<T>()), 0.5);
};

//==================================================================================================
// phi  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of phi on scalar", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::lower;
  using eve::upper;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::phi[eve::lower](as<T>()), eve::phi[eve::upper](as<T>()))));
};


//==================================================================================================
// simd Tests for masked phi
//==================================================================================================
TTS_CASE_WITH("Check behavior of phi[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::phi[mask](eve::as(a0)), eve::if_else(mask, eve::phi(eve::as(a0)), eve::zero));
};
