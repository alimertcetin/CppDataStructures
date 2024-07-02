#include <iostream>
#include <typeinfo>
#include "List.hpp"
#include "HashSet.hpp"
#include "LinkedList.hpp"

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
  //HashSet<int> hashSet;
  //Test(list);
  //Test(hashSet);

  LinkedList<int> linkedList;
  int num = 10;
  for (int i = 0; i < num; ++i) {
    linkedList.AddLast(i);
  }

  LinkedList<int>::Node* half = linkedList.Find(num/2);
  linkedList.AddAfter(*half, 999999);
  linkedList.AddBefore(*half, 111111);
  linkedList.Remove(half);
  linkedList.Remove(half);
  linkedList.AddFirst(900000);
  
  LinkedList<int>::Node* current = linkedList.head();
  while (current != nullptr) {
    std::cout << current->value() << "\n";
    current = current->next();
  }
  
  std::cout << linkedList.count() << "\n";
  linkedList.Clear();
  std::cout << linkedList.count() << "\n";
  
}
