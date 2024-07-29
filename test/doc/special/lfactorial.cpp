// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i+c/2);});
  eve::wide wi = {93, 25, 32, 180, 1, 2, 3, 4};
  eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;});

  std::cout << "<- wf             = " << wf << "\n";
  std::cout << "<- wi             = " << wi << "\n";
  std::cout << "<- wu             = " << wu << "\n";

  std::cout << "-> lfactorial(wf) = " << eve::lfactorial(wf) << "\n";
  std::cout << "-> lfactorial(wi) = " << eve::lfactorial(wi) << "\n";
  std::cout << "-> lfactorial(wu) = " << eve::lfactorial(wu) << "\n";
}
