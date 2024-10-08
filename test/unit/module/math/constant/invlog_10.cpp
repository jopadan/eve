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
TTS_CASE_TPL("Check return types of invlog10", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::invlog_10(as<T>()), T);
  TTS_EXPR_IS(eve::invlog_10(as<v_t>()), v_t);
};
//==================================================================================================
// invlog_10  tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of invlog_10 on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::lower;
  using eve::upper;
  TTS_EQUAL(eve::invlog_10(as<T>()), T(0.43429448190325182765112891891660508229439700580367l));
};

//==================================================================================================
// invlog_10  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of invlog_10 on scalar", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::lower;
  using eve::upper;
  using elt_t = eve::element_type_t<T>;
  if constexpr( sizeof(long double) > sizeof(elt_t) )
  {
    TTS_EXPECT(eve::invlog_10[eve::lower](as<elt_t>())
               < 0.43429448190325182765112891891660508229439700580367l);
    TTS_EXPECT(eve::invlog_10[eve::upper](as<elt_t>())
               > 0.43429448190325182765112891891660508229439700580367l);
  }
  TTS_EXPECT(eve::all(eve::test::is_near(eve::next(eve::invlog_10[eve::lower](as<T>())), eve::invlog_10[eve::upper](as<T>()))));
};


//==================================================================================================
// simd Tests for masked invlog_10
//==================================================================================================
TTS_CASE_WITH("Check behavior of invlog_10[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::invlog_10[mask](eve::as(a0)), eve::if_else(mask, eve::invlog_10(eve::as(a0)), eve::zero));
};
