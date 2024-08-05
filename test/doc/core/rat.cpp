// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wf1{0.0, -4.0, 1.0, -1.0, 2.0, -2.0, 3.0, -3.0};

  std::cout << "<- wf0           = " << wf0 << "\n";
  std::cout << "<- wf1           = " << wf1 << "\n";
                                 
  std::cout << "-> rat(wf0)      = " << eve::rat(wf0) << "\n";
  std::cout << "-> rat(wf0, wf1) = " << eve::rat(wf0, wf1) << "\n";
}
