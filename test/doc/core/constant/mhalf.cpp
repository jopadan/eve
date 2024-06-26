#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_mhalf() { return eve::mhalf(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> mhalf(as<wide_ft>())  = " << eve::mhalf(eve::as<wide_ft>()) << std::endl
            << "-> mhalf(as(wxf))        = " << eve::mhalf(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> mhalf(as<float>())         = " << eve::mhalf(eve::as(float())) << std::endl
            << "-> mhalf(as<xf))              = " << eve::mhalf(eve::as(xf)) << std::endl;

  std::cout << "-> constexpr mhalf            = " << constexpr_mhalf<float>() << std::endl;

  return 0;
}
