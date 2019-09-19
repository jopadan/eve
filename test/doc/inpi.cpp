#include <eve/function/inpi.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp> 
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<8>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, eve::Pio_2<float>()
                 ,eve::Pi<float>(), eve::Inf<float>(), eve::Minf<float>(), eve::Nan<float>() };

  std::cout
    << "---- simd" << '\n'
    << "<- pf =                  " << pf << '\n'
    << "-> eve::inpi(pf) =      " << eve::inpi(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::Pi<float>();

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf =                  " << xf << '\n'
    << "-> eve::inpi(xf) =      " << eve::inpi(xf) << '\n'
    << "<- yf =                  " << yf << '\n'
    << "-> eve::inpi(yf) =      " << eve::inpi(yf) << '\n';
  return 0;
}
