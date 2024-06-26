#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_invlog_10() { return eve::invlog_10(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> invlog_10(as<wide_ft>())       = " << eve::invlog_10(eve::as<wide_ft>())            << std::endl
            << "-> invlog_10(as(wxf))             = " << eve::invlog_10(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> invlog_10(as<float>())         = " << eve::invlog_10(eve::as(float())) << std::endl
            << "-> invlog_10(as<xf))              = " << eve::invlog_10(eve::as(xf))      << std::endl;


  std::cout << "-> constexpr invlog_10            = " << constexpr_invlog_10<float>() << std::endl;

  return 0;
}
