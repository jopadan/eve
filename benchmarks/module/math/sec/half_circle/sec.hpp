//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <cmath>

int main()
{
  auto lmax = eve::Rempio2_limit[eve::half_circle](eve::as<EVE_VALUE>());
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__sec = [](auto x){return 1/std::cos(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__sec) , xp, std__sec , arg0);
  run<EVE_VALUE>(EVE_NAME(sec[eve::half_circle]) , xp, eve::sec[eve::half_circle] , arg0);
  run<EVE_TYPE> (EVE_NAME(sec[eve::half_circle]) , xp, eve::sec[eve::half_circle] , arg0);

}
