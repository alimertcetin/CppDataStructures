#include <iostream>
#include "List.hpp"

int main(int argc, char* argv[])
{
  List<int> l;
  for (int i = 0; i < 100; ++i) {
    l.Add(i);
  }

  for (int i = 0; i < l.count(); ++i) {
    std::cout << l[i] << "\n";

  }

  l.Clear();
  std::cout << l.count() << "\n";

}
