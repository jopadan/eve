//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

enum class some_enum : std::int16_t {};

TTS_CASE_TPL("Check basic constants behavior", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_IEEE_EQUAL(eve::allbits(as<T>()), eve::bit_not(T(0)));
  TTS_EQUAL(eve::true_(as<T>()), eve::as_logical_t<T>(true));
  TTS_EQUAL(eve::false_(as<T>()), eve::as_logical_t<T>(false));
  TTS_EQUAL(eve::one(as<T>()), T(1));
  TTS_EQUAL(eve::mone(as<T>()), T(-1));
  TTS_EQUAL(eve::zero(as<T>()), T(0));

  if constexpr( eve::floating_value<T> )
  {
    TTS_IEEE_EQUAL(eve::allbits(as<T>()), T(0.0 / 0.0));
    TTS_EQUAL(eve::mzero(as<T>()), T(-0));
    TTS_EQUAL(eve::half(as<T>()), T(0.5));
    TTS_EQUAL(eve::mhalf(as<T>()), T(-0.5));
    TTS_EXPECT(eve::all(eve::is_negative(eve::mzero(as<T>()))));
  }
};

TTS_CASE("Check basic constants behavior - translation type")
{
  using eve::as;
  TTS_EQUAL(eve::true_(as<some_enum>()), eve::logical<std::int16_t>(true));
  TTS_EQUAL(eve::false_(as<some_enum>()), eve::logical<std::int16_t>(false));
  TTS_EQUAL(eve::one(as<some_enum>()), some_enum{1});
  TTS_EQUAL(eve::mone(as<some_enum>()), some_enum{-1});
  TTS_EQUAL(eve::zero(as<some_enum>()), some_enum{0});
  TTS_EQUAL(eve::allbits(as<some_enum>()), some_enum{~0});
};

TTS_CASE_TPL("Check ieee754 constants", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::as;
  using elt_t = eve::element_type_t<T>;
  using ilt_t = eve::as_integer_t<elt_t>;
  using i_t   = eve::as_integer_t<T, signed>;
  using u_t   = eve::as_integer_t<T, unsigned>;
  TTS_EQUAL(eve::bitincrement(as<T>()), T(eve::bit_cast(eve::one(as<ilt_t>()), as<elt_t>())));
  TTS_EQUAL(eve::signmask(as<T>()),
            T(eve::bit_cast(ilt_t(1LL << (sizeof(ilt_t) * 8 - 1)), as<elt_t>())));
  TTS_EQUAL(eve::mindenormal(as<T>()), eve::bitincrement(as<T>()));

  if constexpr( std::same_as<elt_t, float> )
  {
    TTS_ULP_EQUAL(eve::sqrteps(as<T>()), eve::sqrt(eve::eps(as<T>())), 0.5);
    TTS_IEEE_EQUAL(eve::nan(as<T>()), T(0.0 / 0.0));
    TTS_EQUAL(eve::eps(as<T>()), T(1.1920929e-7));
    TTS_EQUAL(eve::exponentmask(as<T>()), i_t(0x7f800000U));
    TTS_EQUAL(eve::maxexponentp1(as<T>()), i_t(128));
    TTS_EQUAL(eve::logeps(as<T>()), T(-15.942384719848632812f));
    TTS_EQUAL(eve::mantissamask(as<T>()), u_t(0x807FFFFFU));
    TTS_EQUAL(eve::oneosqrteps(as<T>()), T(2896.309326171875f));
    TTS_EQUAL(eve::maxexponent(as<T>()), i_t(127));
    TTS_EQUAL(eve::maxexponentm1(as<T>()), i_t(126));
    TTS_EQUAL(eve::nbmantissabits(as<T>()), i_t(23));
    TTS_EQUAL(eve::twotonmb(as<T>()), T(8388608));
  }
  else if constexpr( std::same_as<elt_t, double> )
  {
    TTS_ULP_EQUAL(eve::sqrteps(as<T>()), eve::sqrt(eve::eps(as<T>())), 0.5);
    TTS_IEEE_EQUAL(eve::nan(as<T>()), T(0.0 / 0.0));
    TTS_EQUAL(eve::eps(as<T>()), T(2.2204460492503130e-16));
    TTS_EQUAL(eve::exponentmask(as<T>()), i_t(0x7ff0000000000000ULL));
    TTS_EQUAL(eve::maxexponentp1(as<T>()), i_t(1024));
    TTS_EQUAL(eve::logeps(as<T>()), T(-36.043653389117156089696070315825181539926006986734));
    TTS_EQUAL(eve::mantissamask(as<T>()), u_t(0x800FFFFFFFFFFFFFULL));
    TTS_EQUAL(eve::oneosqrteps(as<T>()), T(67108864.0));
    TTS_EQUAL(eve::maxexponent(as<T>()), i_t(1023));
    TTS_EQUAL(eve::maxexponentm1(as<T>()), i_t(1022));
    TTS_EQUAL(eve::nbmantissabits(as<T>()), i_t(52));
    TTS_EQUAL(eve::twotonmb(as<T>()), T(4503599627370496));
  }
};

TTS_CASE_TPL("Check basic masked constants behavior", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::as;
  using elt_t = eve::element_type_t<T>;
  using i_t   = eve::as_integer_t<T, signed>;

  T p{[](auto i, auto){return i; }};
  auto test = [p](auto a){return eve::if_else(p > 1, a, eve::zero); };
  TTS_IEEE_EQUAL(eve::allbits[p > 1](as<T>()), test(eve::bit_not(T(0))));
  TTS_EQUAL(eve::true_[p > 1](as<T>()), test(eve::as_logical_t<T>(true)));
  TTS_EQUAL(eve::false_[p > 1](as<T>()), test(eve::as_logical_t<T>(false)));
  TTS_EQUAL(eve::one[p > 1](as<T>()), test(T(1)));
  TTS_EQUAL(eve::mone[p > 1](as<T>()), test(T(-1)));
  TTS_EQUAL(eve::zero[p > 1](as<T>()), test(T(0)));

  if constexpr( eve::floating_value<T> )
  {
    TTS_IEEE_EQUAL(eve::allbits[p > 1](as<T>()), test(T(0.0 / 0.0)));
    TTS_EQUAL(eve::mzero[p > 1](as<T>()), test(T(-0)));
    TTS_EQUAL(eve::half[p > 1](as<T>()), test(T(0.5)));
    TTS_EQUAL(eve::mhalf[p > 1](as<T>()), test(T(-0.5)));
    if constexpr( std::is_same_v<elt_t, double> )
    {
      TTS_EQUAL(eve::eps[p > 1](as<T>()), test(T(2.2204460492503130e-16)));
      TTS_EQUAL(eve::exponentmask[p > 1](as<T>()), test(i_t(0x7ff0000000000000ULL)));
    }
    else
    {
      TTS_EQUAL(eve::eps[p > 1](as<T>()), test(T(1.1920929e-7)));
      TTS_EQUAL(eve::exponentmask[p > 1](as<T>()), test(i_t(0x7f800000U)));
    }
  }

  TTS_IEEE_EQUAL(eve::allbits[eve::ignore_none](as<T>()), eve::allbits(as<T>()));
  TTS_EQUAL(eve::true_[eve::ignore_none](as<T>()), eve::true_(as<T>()));
  TTS_EQUAL(eve::false_[eve::ignore_none](as<T>()),eve::false_(as<T>()));
  TTS_EQUAL(eve::one[eve::ignore_none](as<T>()), T(1));
  TTS_EQUAL(eve::mone[eve::ignore_none](as<T>()), T(-1));
  TTS_EQUAL(eve::zero[eve::ignore_none](as<T>()), T(0));

  TTS_IEEE_EQUAL(eve::allbits[eve::ignore_all](as<T>()), eve::zero(as<T>()));
  TTS_EQUAL(eve::true_[eve::ignore_all](as<T>()), eve::false_(as<T>()));
  TTS_EQUAL(eve::false_[eve::ignore_all](as<T>()), eve::false_(as<T>()));
  TTS_EQUAL(eve::one[eve::ignore_all](as<T>()), eve::zero(as<T>()));
  TTS_EQUAL(eve::mone[eve::ignore_all](as<T>()), eve::zero(as<T>()));
  TTS_EQUAL(eve::zero[eve::ignore_all](as<T>()), eve::zero(as<T>()));

  if constexpr( eve::floating_value<T> )
  {
    TTS_IEEE_EQUAL(eve::allbits[eve::ignore_none](as<T>()), (T(0.0 / 0.0)));
    TTS_EQUAL(eve::mzero[eve::ignore_none](as<T>()), (T(-0)));
    TTS_EQUAL(eve::half[eve::ignore_none](as<T>()), (T(0.5)));
    TTS_EQUAL(eve::mhalf[eve::ignore_none](as<T>()), (T(-0.5)));
    if constexpr( std::is_same_v<elt_t, double> )
    {
      TTS_EQUAL(eve::eps[eve::ignore_none](as<T>()), T(2.2204460492503130e-16));
      TTS_EQUAL(eve::exponentmask[eve::ignore_none](as<T>()), i_t(0x7ff0000000000000ULL));
    }
    else
    {
      TTS_EQUAL(eve::eps[eve::ignore_none](as<T>()), T(1.1920929e-7));
      TTS_EQUAL(eve::exponentmask[eve::ignore_none](as<T>()), i_t(0x7f800000U));
    }
  }
};
