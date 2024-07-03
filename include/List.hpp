#pragma once
#include <stdexcept>
#include <type_traits>
#include <utility>

template<typename T>
class List
{
private:
  T* arr;
  int mcount;
  int mcapacity;

  void Resize(int newSize);

public:
  class Iter
  {
  private:
    List<T>* list;
    int idx;
  public:
    Iter(List<T>* list, int idx);

    bool operator==(const Iter& other) const;
    bool operator!=(const Iter& other) const;
    Iter& operator++();
    Iter operator++(int);
    T& operator*() const;
  };
  
  List();
  virtual ~List();

  void Add(T item);
  bool Remove(T item);
  bool RemoveAt(int index);
  int IndexOf(T item);
  void Clear();

  Iter begin();
  Iter end();
  
  int count();
  int capacity();
  bool operator==(const List<T>& other) const;
  bool operator!=(const List<T>& other) const;
  T& operator[](int index);
};

template<typename T>
List<T>::List()
{
    mcapacity = 2;
    mcount = 0;
    arr = new T[mcapacity];
}

template<typename T>
List<T>::~List()
{
  Clear();
  delete[] arr;
}

template<typename T>
void List<T>::Resize(int newSize)
{
    T* newArr = new T[newSize];
    for (int i = 0; i < newSize && i < mcapacity; ++i)
    {
        newArr[i] = arr[i];
    }
    mcapacity = newSize;
    if (mcount > mcapacity)
        mcount = mcapacity;
    delete[] arr;
    arr = newArr;
}

template<typename T>
void List<T>::Add(T item)
{
    if (mcapacity == mcount)
    {
        Resize(mcapacity * 2);
    }
    arr[mcount] = item;
    mcount++;
}

template<typename T>
bool List<T>::Remove(T item)
{
    return RemoveAt(IndexOf(item));
}

template<typename T>
bool List<T>::RemoveAt(int index)
{
    if (index < 0 || index >= mcount) return false;
    for (int i = index; i < mcount - 1; ++i)
    {
      arr[i] = std::move(arr[i + 1]);
    }
    mcount--;
    return true;
}

template<typename T>
int List<T>::IndexOf(T item)
{
    for (int i = 0; i < mcount; ++i)
    {
        if (item == arr[i]) return i;
    }
    return -1;
}

template<typename T>
void List<T>::Clear()
{
    // If T is a pointer type, delete each element
    if constexpr (std::is_pointer_v<T>) {
        for (int i = 0; i < mcount; ++i) {
            delete arr[i];
	    arr[i] = nullptr;
        }
    }
    mcount = 0;
}

template<typename T>
int List<T>::count()
{
    return mcount;
}

template<typename T>
int List<T>::capacity()
{
    return mcapacity;
}

template<typename T>
T& List<T>::operator[](int index)
{
    if (index < 0 || index >= mcount)
    {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}

template<typename T>
bool List<T>::operator==(const List<T> &other) const
{
  if (this == &other)
        return true;

    if (mcount != other.mcount)
        return false;
    
    for (int i = 0; i < mcount; ++i) {
        if (arr[i] != (*other.arr[i]))
            return false;
    }

    return true;
}

template<typename T>
bool List<T>::operator!=(const List<T> &other) const
{
  return !(*this == other);
}

// iterator
template<typename T>
typename List<T>::Iter List<T>::begin()
{
  return List<T>::Iter(this, 0);
}

template<typename T>
typename List<T>::Iter List<T>::end()
{
  return List<T>::Iter(this, this->mcount);
}

template<typename T>
List<T>::Iter::Iter(List<T>* list, int idx) : list(list), idx(idx)
{
  
}

template<typename T>
bool List<T>::Iter::operator==(const List<T>::Iter& other) const
{
  return list == other.list && idx == other.idx;
}

template<typename T>
bool List<T>::Iter::operator!=(const List<T>::Iter& other) const
{
  return !(*this == other);
}

template<typename T>
typename List<T>::Iter& List<T>::Iter::operator++()
{
  idx++;
  return *this;
}

template<typename T>
typename List<T>::Iter List<T>::Iter::operator++(int)
{
  List<T>::Iter tmp(*this);
  idx++;
  return tmp;
}

template<typename T>
T& List<T>::Iter::operator*() const
{
  return list->operator[](idx);
}
