// revision 1
#include <eve/module/math.hpp>
#include <iostream>
#include <cmath>

int main()
{
  eve::wide qf = {0.0f, 3.0f, -4.0f, 2.0f, 2.0f,
                  eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  eve::wide pf = {4.0f, 1.0f, -1.0f,  0.5f,  0.0f, 0.0f, -0.0f,  2.5f};

  std::cout << "<- pf                         = " << pf << "\n";
  std::cout << "<- qf                         = " << qf << "\n";

  std::cout << "-> pow(pf, qf)                = " << eve::pow(pf, qf) << "\n";
  std::cout << "-> pow[ignore_last(2)](pf, qf)= " << eve::pow[eve::ignore_last(2)](pf, qf) << "\n";
  std::cout << "-> pow[qf > 0.0f](pf, qf)     = " << eve::pow[qf > 0.0f](pf, qf) << "\n";
  std::cout << "-> pow[raw](pf, qf)           = " << eve::pow[eve::raw](pf, qf) << "\n";
}
