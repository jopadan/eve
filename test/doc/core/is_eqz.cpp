// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -0.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wf0                         = " << wf0 << "\n";
  std::cout << "<- wi0                         = " << wi0 << "\n";
  std::cout << "<- wu0                         = " << wu0 << "\n";

  std::cout << "-> is_eqz(wf0)                 = " << eve::is_eqz(wf0) << "\n";
  std::cout << "-> is_eqz[ignore_last(2)](wf0) = " << eve::is_eqz[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> is_eqz[wf0 != 0](wf0)       = " << eve::is_eqz[wf0 != 0](wf0) << "\n";
  std::cout << "-> is_eqz(wu0)                 = " << eve::is_eqz(wu0) << "\n";
  std::cout << "-> is_eqz[ignore_last(2)](wu0) = " << eve::is_eqz[eve::ignore_last(2)](wu0) << "\n";
  std::cout << "-> is_eqz[wu0 != 0](wu0)       = " << eve::is_eqz[wu0 != 0](wu0) << "\n";
  std::cout << "-> is_eqz(wi0)                 = " << eve::is_eqz(wi0) << "\n";
  std::cout << "-> is_eqz[ignore_last(2)](wi0) = " << eve::is_eqz[eve::ignore_last(2)](wi0) << "\n";
  std::cout << "-> is_eqz[wi0 != 0](wi0)       = " << eve::is_eqz[wi0 != 0](wi0) << "\n";
}
