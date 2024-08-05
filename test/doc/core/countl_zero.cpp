// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wu0                              = " << wu0 << "\n";
                                                    
  std::cout << "-> countl_zero(wu0)                 = " << eve::countl_zero(wu0) << "\n";
  std::cout << "-> countl_zero[ignore_last(2)](wu0) = " << eve::countl_zero[eve::ignore_last(2)](wu0) << "\n";
  std::cout << "-> countl_zero[wu0 != 0](wu0)       = " << eve::countl_zero[wu0 != 0](wu0) << "\n";
}
