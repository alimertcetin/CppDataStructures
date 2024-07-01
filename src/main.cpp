#include <iostream>
#include <typeinfo>
#include "List.hpp"
#include "HashSet.hpp"

template<typename T>
void Populate(T& list)
{
  std::cout << "add: " << typeid(list).name() << "\n";
  
  for (int i = 0; i < 100; ++i) {
    list.Add(i);
  }
}

template<typename T>
void Log(T& list)
{
  
  for (auto it = list.begin(); it != list.end(); it++)
    {
      std::cout << *it << "\n";
    }
}

template<typename T>
void Clear(T& list)
{
  std::cout << "clear: " << typeid(list).name() << "\n";

  list.Clear();
  
  std::cout << list.count() << "\n";
}

template<typename T>
void Test(T& list)
{
  Populate(list);
  Log(list);
  Clear(list);
}

int main(int argc, char* argv[])
{
  //List<int> list;
  HashSet<int> hashSet;
  //Test(list);
  Test(hashSet);
}
