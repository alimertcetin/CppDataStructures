#pragma once

template<typename T>
class List
{
private:
  T* arr;
  int mcount;
  int mcapacity;

  void Resize(int newSize);

public:
  List();
  virtual ~List();

  void Add(T item);
  bool Remove(T item);
  bool RemoveAt(int index);
  int IndexOf(T item);
  void Clear();
  
  int count();
  int capacity();
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
