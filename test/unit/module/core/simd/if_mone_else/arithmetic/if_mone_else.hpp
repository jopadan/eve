//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IF_MONE_ELSE_HPP
#define IF_MONE_ELSE_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/constant/mone.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <type_traits>

using eve::fixed;

TTS_CASE_TPL("Check if_mone_else behavior on homogeneous wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::is_nez;
  using eve::wide;

  wide<Type, T> cond([](auto i, auto) { return (i % 2) * i; }),
      rhs1([](auto i, auto) { return i % 2 + 1; }), rhs2([](auto i, auto) { return i % 3; });

  auto z  = eve::Mone<wide<Type, T>>();
  auto z_ = eve::mone_;
  TTS_IEEE_EQUAL(eve::if_else(cond, z, rhs1), eve::if_else(cond, z_, rhs1));
}

TTS_CASE_TPL("Check if_mone_else behavior on wide + scalar",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::is_nez;
  using eve::wide;

  wide<Type, T> lhs([](int i, int) { return i % 3; });

  auto z  = eve::Mone<wide<Type, T>>();
  auto z_ = eve::mone_;
  TTS_IEEE_EQUAL(eve::if_else(lhs, z, Type(7)), eve::if_else(lhs, z_, Type(7)));
}

#endif
