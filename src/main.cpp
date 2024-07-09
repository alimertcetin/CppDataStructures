#include <iostream>
#include <typeinfo>
#include "List.hpp"
#include "HashSet.hpp"
#include "LinkedList.hpp"
#include "Queu.hpp"

template <typename T> void Populate(T &list);
template <typename T> void Log(T &list);
template <typename T> void Clear(T &list);
template <typename T> void TestGenericList(T &list);
void TestLinkedList(LinkedList<int> &list);
void TestQueu(Queu<int> &list);

int main(int argc, char* argv[])
{
  //List<int> list;
  //Test(list);
  //HashSet<int> hashSet;
  //Test(hashSet);
  // LinkedList<int> linkedList;
  // TestLinkedList(linkedList);
  Queu<int> queu;
  TestQueu(queu);
}

template<typename T>
void Populate(T& list)
{
  std::cout << "----Add: " << typeid(list).name() << "\n";
  for (int i = 0; i < 100; ++i) {
    list.Add(i);
  }
}

template<typename T>
void Log(T& list)
{
  std::cout << "----Log: " << typeid(list).name() << "\n";
  for (auto it = list.begin(); it != list.end(); ++it) {
    std::cout << *it << "\n";
  }
}

template<typename T>
void Clear(T& list)
{
  std::cout << "----Clear: " << typeid(list).name() << "\n";
  std::cout << "Count before clear: " << list.count() << "\n";
  list.Clear();
  std::cout << "Count after clear: " << list.count() << "\n";
}

template<typename T>
void TestGenericList(T& list)
{
  Populate(list);
  Log(list);
  Clear(list);
}

void TestLinkedList(LinkedList<int>& list)
{
  int num = 10;
  for (int i = 0; i < num; ++i) {
    list.AddLast(i);
  }

  LinkedList<int>::Node* half = list.Find(num/2);
  list.AddAfter(*half, 999999);
  list.AddBefore(*half, 111111);
  list.Remove(half);
  list.Remove(half);
  list.AddFirst(900000);
  Log(list);
  Clear(list);
}

void TestQueu(Queu<int>& list)
{
  int num = 10;
  for (int i = 0; i < num; ++i) {
    list.Enqueu(i);
  }

  Log(list);
  std::cout << list.Dequeu() << "\n";
  std::cout << list.Dequeu() << "\n";
  Clear(list);

}
