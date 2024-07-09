#pragma once
#include <stdexcept>
#include <type_traits>
#include <utility>

template<typename T>
class Queu
{
private:
  static constexpr int SHRINK_THRESHOLD = 32;
  T* arr;
  int mhead;
  int mtail;
  int mcapacity;
  void Resize(int newSize);
  void Organize();
public:
  Queu();
  virtual ~Queu();

  void Enqueu(T item);
  T& Dequeu();
  void Clear();
  int count(); //tail - head

  T* begin();
  T* end();
};

template <typename T>
Queu<T>::Queu() : arr(new T[2]), mhead(0), mtail(0), mcapacity(2)
{
  
}

template <typename T>
Queu<T>::~Queu()
{
  Clear();
  delete[] arr;
}

template<typename T>
void Queu<T>::Organize()
{
  if (mhead == 0) return; // There is no space to move items
  
  int idx = 0;
  for (int i = mhead; i < mtail; ++i) {
    arr[idx] = std::move(arr[i]);
    idx++;
  }
  mtail -= mhead;
  mhead = 0;
}


template<typename T>
void Queu<T>::Resize(int newSize)
{
  T* newArr = new T[newSize];
  for (int i = 0; i < mcapacity && i < newSize; ++i) {
    newArr[i] = std::move(arr[i]);
  }
  mcapacity = newSize;
  delete[] arr;
  arr = newArr;
}

// TODO: Organize array
// If after organizing the array still requires resize than resize

template<typename T>
void Queu<T>::Enqueu(T item)
{
  if (mtail == mcapacity) {
    Organize();
    if (mtail == mcapacity) 
      Resize(mcapacity * 2);
  }
  arr[mtail] = std::move(item);
  mtail++;
}

template<typename T>
T& Queu<T>::Dequeu()
{
  if (mhead == mtail) {
    throw std::logic_error("There is nothing to Dequeu.");
  }
  if (mhead == SHRINK_THRESHOLD) {
      Organize();
  }
  mhead++;
  return arr[mhead - 1];
}


template<typename T>
int Queu<T>::count()
{ return mtail - mhead; }

template <typename T>
void Queu<T>::Clear() {
  if constexpr (std::is_pointer_v<T>) {
    for (int i = mhead; i < mtail; ++i) {
      delete arr[i];
      arr[i] = nullptr;
    }
  }
  mhead = 0;
  mtail = 0;
}

template<typename T>
T* Queu<T>::begin()
{ return arr + mhead; }

template<typename T>
T* Queu<T>::end()
{ return arr + mtail; }
