//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"

#include <eve/module/elliptic.hpp>

TTS_CASE_TPL ( "Check jacobi_elliptic over real"
             , eve::test::scalar::ieee_reals
             )
  <typename T>(tts::type<T>)
{
  auto pr = tts::prec<T>(1.0e-4, 1.0e-8);
  using a_t  = std::array<T, 7 >;
  a_t phi= {0.000000000000000e+00, 1.346396851538483e+00, 2.692793703076966e+00, 4.039190554615448e+00, 5.385587406153931e+00, 6.731984257692414e+00, 8.078381109230897e+00, };
  a_t m= {0.000000000000000e+00, 1.428571428571428e-01, 2.857142857142857e-01, 4.285714285714285e-01, 5.714285714285714e-01, 7.142857142857143e-01, 8.571428571428572e-01, };
  a_t cn= {1.000000000000000e+00, 2.617519826024742e-01, -7.631598723534548e-01, -9.058217538883415e-01, -2.454936799580787e-01, 2.388574482052262e-01, 3.443384696011595e-01, };
  a_t sn= {0.000000000000000e+00, 9.651351716747629e-01, 6.462097254215990e-01, -4.236590022443154e-01, -9.693981911993855e-01, -9.710546428687150e-01, -9.388455774794550e-01, };
  a_t dn= {1.000000000000000e+00, 9.310910727586769e-01, 9.384505452789936e-01, 9.607689739736048e-01, 6.804482333199239e-01, 5.713723332988446e-01, 4.944569734110357e-01, };
  //results are taken from octave 9.2.0 ellipj outputs
  for(int i=0; i < 7; ++i)
  {
    auto mm = eve::sqrt(m[i]);
    auto [sni, cni, dni] = eve::jacobi_elliptic(phi[i], mm);
    mm = eve::asin(mm);
    auto [msni, mcni, mdni] = eve::jacobi_elliptic[eve::modular](phi[i], mm);
    auto [esni, ecni, edni] = eve::jacobi_elliptic[eve::eccentric](phi[i], m[i]);
    TTS_RELATIVE_EQUAL(sni, sn[i], pr);
    TTS_RELATIVE_EQUAL(msni, sni, pr);
    TTS_RELATIVE_EQUAL(esni, sni, pr);
    TTS_RELATIVE_EQUAL(cni, cn[i], pr);
    TTS_RELATIVE_EQUAL(mcni, cni, pr);
    TTS_RELATIVE_EQUAL(ecni, cni, pr);
    TTS_RELATIVE_EQUAL(dni, dn[i], pr);
    TTS_RELATIVE_EQUAL(mdni, dni, pr);
    TTS_RELATIVE_EQUAL(edni, dni, pr);
  }
};
