#pragma once
#include <functional>
#include "List.hpp"

template<typename T>
class HashSet
{
private:
  static constexpr int BUCKET_COUNT = 10;
  List<List<T>*>* buckets;
  int mcount;
  int GetBucket(T item);

public:
  
  HashSet();
  virtual ~HashSet();

  class Iter
  {
  private:
    HashSet<T>* hashSet;
    int bucketIndex;
    int elementIndex;

    void advanceToNextValid();
    
  public:
    Iter(HashSet<T>* hashSet, int bucketIndex, int elementIndex);

    static Iter begin(HashSet<T>* hashSet);
    static Iter end(HashSet<T>* hashSet);

    bool operator==(const Iter& other) const;
    bool operator!=(const Iter& other) const;
    T& operator*() const;
    Iter& operator++();
    Iter operator++(int);
  };


  void Add(T item);
  bool Remove(T item);
  void Clear();

  int count();

  Iter begin();
  Iter end();

  bool operator==(const HashSet& other) const;
  bool operator!=(const HashSet& other) const;
};

template<typename T>
HashSet<T>::HashSet()
{
    mcount = 0;
    buckets = new List<List<T>*>();
    for (int i = 0; i < BUCKET_COUNT; ++i) {
        buckets->Add(new List<T>());
    }
}

template<typename T>
HashSet<T>::~HashSet()
{
    Clear();
    delete buckets;
}

template<typename T>
int HashSet<T>::GetBucket(T item)
{
    return std::hash<T>{}(item) % BUCKET_COUNT;
}

template<typename T>
void HashSet<T>::Add(T item)
{
    buckets->operator[](GetBucket(item))->Add(item);
    mcount++;
}

template<typename T>
bool HashSet<T>::Remove(T item)
{
    if (buckets->operator[](GetBucket(item))->Remove(item)) {
        mcount--;
        return true;
    }
    return false;
}

template<typename T>
void HashSet<T>::Clear()
{
  if (buckets->count() == 0) return;
  
  for (int i = 0; i < BUCKET_COUNT; ++i) {
    buckets->operator[](i)->Clear();
    delete buckets->operator[](i);
    buckets->operator[](i) = nullptr;
  }

  buckets->Clear();
  mcount = 0;
}

template<typename T>
int HashSet<T>::count()
{
    return mcount;
}

template<typename T>
bool HashSet<T>::operator==(const HashSet<T> &other) const
{
  if (this == &other)
        return true;

    if (mcount != other.mcount)
        return false;

    // Compare content of each bucket
    for (int i = 0; i < BUCKET_COUNT; ++i) {
        if (!buckets->operator[](i)->operator==(*other.buckets->operator[](i)))
            return false;
    }

    return true;
}

template<typename T>
bool HashSet<T>::operator!=(const HashSet<T> &other) const
{
  return !(*this == other);
}

// Iterator
template<typename T>
HashSet<T>::Iter::Iter(HashSet<T>* hashSet, int bucketIndex, int elementIndex)
    : hashSet(hashSet), bucketIndex(bucketIndex), elementIndex(elementIndex)
{
    advanceToNextValid();
}

template<typename T>
void HashSet<T>::Iter::advanceToNextValid()
{
  while (bucketIndex < hashSet->BUCKET_COUNT) {
    if (elementIndex < hashSet->buckets->operator[](bucketIndex)->count()) {
      return;
    }
    bucketIndex++;
    elementIndex = 0;
  }
}

template<typename T>
typename HashSet<T>::Iter HashSet<T>::Iter::begin(HashSet<T>* hashSet)
{
  return HashSet<T>::Iter(hashSet, 0, 0);
}

template<typename T>
typename HashSet<T>::Iter HashSet<T>::Iter::end(HashSet<T>* hashSet)
{
  return HashSet<T>::Iter(hashSet, hashSet->BUCKET_COUNT, 0);
}

template<typename T>
typename HashSet<T>::Iter HashSet<T>::begin()
{
  return HashSet<T>::Iter::begin(this);
}

template<typename T>
typename HashSet<T>::Iter HashSet<T>::end()
{
  return HashSet<T>::Iter::end(this);
}

template<typename T>
bool HashSet<T>::Iter::operator==(const HashSet<T>::Iter& other) const
{
  return elementIndex == other.elementIndex && bucketIndex == other.bucketIndex && hashSet == other.hashSet;
}

template<typename T>
bool HashSet<T>::Iter::operator!=(const HashSet<T>::Iter& other) const
{
  return !(*this == other);
}

template<typename T>
T& HashSet<T>::Iter::operator*() const
{
  return hashSet->buckets->operator[](bucketIndex)->operator[](elementIndex);
}

template<typename T>
typename HashSet<T>::Iter& HashSet<T>::Iter::operator++()
{
  elementIndex++;
  advanceToNextValid();
  return *this;
}

template<typename T>
typename HashSet<T>::Iter HashSet<T>::Iter::operator++(int)
{
  HashSet<T>::Iter tmp(*this);
  elementIndex++;
  advanceToNextValid();
  return tmp;
}
