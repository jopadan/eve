#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_maxlog() { return eve::maxlog(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> maxlog(as<wide_ft>())        = " << eve::maxlog(eve::as<wide_ft>())            << std::endl
            << "-> maxlog(as(wxf))              = " << eve::maxlog(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> maxlog(as<float>())         = " << eve::maxlog(eve::as(float())) << std::endl
            << "-> maxlog(as<xf))              = " << eve::maxlog(eve::as(xf))      << std::endl;


  std::cout << "-> constexpr maxlog            = " << constexpr_maxlog<float>() << std::endl;

  return 0;
}
