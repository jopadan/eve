//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/polynomial.hpp>

#if defined(__cpp_lib_math_special_functions)
# define NAMESPACE std
# define EVE_HAS_MATH
#else
# if __has_include(<boost/math/special_functions/hermite.hpp>)
#   include <boost/math/special_functions/hermite.hpp>
#   define EVE_HAS_MATH
#   define NAMESPACE boost::math
# endif
#endif

#if defined(EVE_HAS_MATH)
//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of hermite on wide", eve::test::simd::ieee_reals

)
<typename T>(tts::type<T>)
{
  using v_t  = eve::element_type_t<T>;
  using wi_t = eve::as_integer_t<T>;
  using i_t  = eve::as_integer_t<v_t>;
  TTS_EXPR_IS(eve::hermite(i_t(), T()), T);
  TTS_EXPR_IS(eve::hermite(wi_t(), T()), T);
  TTS_EXPR_IS(eve::hermite(i_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::hermite(wi_t(), v_t()), T);
};

//==================================================================================================
//== hermite tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of hermite on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::between(-1.0, 1.0), tts::as_integer(tts::ramp(0))))
<typename T, typename I>(T const& a0, I const& i0)
{
  using v_t          = eve::element_type_t<T>;
  auto eve__hermitev = [](auto n, auto x) { return eve::hermite(n, x); };
  for( unsigned int n = 0; n < 5; ++n )
  {
    auto std_hermite = [&](auto i, auto) { return NAMESPACE::hermite(n, a0.get(i)); };
    TTS_ULP_EQUAL(eve__hermitev(n, a0), T(std_hermite), 16);
  }
   auto std_hermitev = [&](auto i, auto) { return NAMESPACE::hermite(i0.get(i), a0.get(i)); };
   TTS_ULP_EQUAL(eve__hermitev(i0, a0), T(std_hermitev), 16);
  for( unsigned int j = 0; j < eve::cardinal_v<T>; ++j )
  {
    auto std_hermite2 = [&](auto i, auto) { return NAMESPACE::hermite(int(i0.get(i)), a0.get(j)); };
    TTS_ULP_EQUAL(eve__hermitev(i0, a0.get(j)), T(std_hermite2), 64);
  }
  for( unsigned int j = 0; j < eve::cardinal_v<T>; ++j )
  {
    for( unsigned int n = 0; n < eve::cardinal_v<T>; ++n )
    {
      TTS_ULP_EQUAL(
        eve__hermitev(i0.get(j), a0.get(n)), v_t(NAMESPACE::hermite(int(i0.get(j)), a0.get(n))), 64);
    }
  }
};
#else
TTS_CASE("Check return types of hermite")
{
  TTS_PASS("SKipping due to no reference available");
};
#endif

