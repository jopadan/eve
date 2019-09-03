#include <eve/function/abs.hpp>
#include <eve/wide.hpp>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};
  wide_it pi = {-1, 2, -3, -32768};

  std::cout << "---- simd" << '\n'
            << "<- pf =                            " << pf << '\n'
            << "-> eve::abs(pf) =                  " << eve::abs(pf) << '\n'
            << "<- pi =                            " << pi << '\n'
            << "-> eve::abs(pi) =                  " << eve::abs(pi) << '\n';

  float        xf = -32768.0f;
  std::int16_t xi = -32768;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                            " << xf << '\n'
            << "-> eve::abs(xf) =                  " << eve::abs(xf) << '\n'
            << "<- xi =                            " << xi << '\n'
            << "-> eve::abs(xi) =                  " << eve::abs(xi) << '\n';
  return 0;
}
