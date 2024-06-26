#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_invlog10_2() { return eve::invlog10_2(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> invlog10_2(as<wide_ft>())       = " << eve::invlog10_2(eve::as<wide_ft>())            << std::endl
            << "-> invlog10_2(as(wxf))             = " << eve::invlog10_2(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> invlog10_2(as<float>())         = " << eve::invlog10_2(eve::as(float())) << std::endl
            << "-> invlog10_2(as<xf))              = " << eve::invlog10_2(eve::as(xf))      << std::endl;


  std::cout << "-> constexpr invlog10_2            = " << constexpr_invlog10_2<float>() << std::endl;

  return 0;
}
