#include <cxxabi.h>

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
#include <sstream>
#include <list>
#include <deque>
#include <iterator>
#include <fstream>
#include <set>
#include <type_traits>
#include <map>
#include <typeinfo>
#include <memory>
#include <cstdlib>
#include <cassert>

using namespace std;
using namespace std::placeholders;

int main() {
  std::cout << " 3 / 2 = " <<  3 / 2 << "\n";
  std::cout << "-3 / 2 = " << -3 / 2 << "\n";

  std::cout  << " 3 >> 1 = " << ( 3 >> 1) << "\n";
  std::cout  << "-3 >> 1 = " << (-3 >> 1) << "\n";

  std::cout << " 21 % -6 = " <<  21 % -6 << "\n";
  std::cout << "-21 %  6 = " << -21 %  6 << "\n";
  std::cout << "-21 % -6 = " << -21 % -6 << "\n";

  assert(-true == true);

  return 0;
}
