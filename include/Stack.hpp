#include <utility>

template<typename T>
class Stack
{
private:
  T* arr;
  int mcapacity;
  int mcount;

  void Resize(int newSize);
public:
  class Iter
  {
  private:
    Stack* stack;
    int idx;
  public:
    Iter(Stack* stack, int idx) : stack(stack), idx(idx)
    {}

    static Iter begin(Stack* stack)
    {
      return Iter(stack, stack->mcount - 1);
    }
    
    static Iter end(Stack* stack)
    {
      return Iter(stack, -1);
    }

    T& operator*()
    {
      return stack->arr[idx];
    }

    Iter& operator++()
    {
      idx--;
      return *this;
    }

    Iter& operator++(int)
    {
      Iter tmp(*this);
      idx--;
      return tmp;
    }

    Iter& operator--()
    {
      idx++;
      return *this;
    }

    bool operator==(const Iter& other) const
    {
      return stack == other.stack && idx == other.idx;
    }

    bool operator !=(const Iter& other) const
    {
      return stack != other.stack || idx != other.idx;
    }
    
  };

  Stack();
  virtual ~Stack();

  void Push(T item);
  T& Pop();

  Iter begin();
  Iter end();

  int capacity() const
  { return mcapacity; }
  
  int count() const
  { return mcount; }

  void Clear();
};

template <typename T>
Stack<T>::Stack() : arr(new T[2]), mcount(), mcapacity(2)
{
  
}

template <typename T> Stack<T>::~Stack<T>()
{
  Clear();
  delete[] arr;
}

template <typename T> void Stack<T>::Resize(int newSize)
{
  T* newArr = new T[newSize];
  for (int i = 0; i < newSize && i < mcount; ++i) {
    newArr[i] = std::move(arr[i]);
  }
  mcapacity = newSize;
  if (mcount >= mcapacity)
    mcount = mcapacity - 1;
  delete[] arr;
  arr = newArr;
}

template<typename T>
void Stack<T>::Push(T item)
{
  if (mcount == mcapacity) {
    Resize(mcapacity * 2);
  }
  arr[mcount] = std::move(item);
  mcount++;
}

template<typename T>
T& Stack<T>::Pop()
{
  return arr[--mcount];
}

template<typename T>
void Stack<T>::Clear()
{
  if constexpr (std::is_pointer_v<T>) {
    for (int i = 0; i < mcount; ++i) {
      delete arr[i];
      arr[i] = nullptr;
    }
  }
  mcount = 0;
}


template<typename T>
typename Stack<T>::Iter Stack<T>::begin()
{
  return Stack<T>::Iter::begin(this);
}

template<typename T>
typename Stack<T>::Iter Stack<T>::end()
{
  return Stack<T>::Iter::end(this);
}
