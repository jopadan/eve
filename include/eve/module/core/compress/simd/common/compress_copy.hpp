//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/compress/detail/compress_callable.hpp>
#include <eve/module/core/compress/compress_copy_scalar.hpp>

namespace eve
{

inline constexpr auto compress_copy = compress_copy_scalar;

}