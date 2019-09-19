//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/atan2pi.hpp>

#define TYPE()        float
#define FUNCTION()    eve::atan2pi
#define SAMPLES(N)    random<T>(N,-100.,100.), random<T>(N,-100.,100.)

#include "bench.hpp"
