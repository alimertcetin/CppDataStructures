#pragma once
#include <iostream>
#include <stdexcept>
#include <utility>

template<typename T>
class LinkedList
{ 
public:
  class Node
  {
    friend class LinkedList;
  private:
    T mvalue;
    Node* mprev;
    Node* mnext;
  public:
    Node(T value, Node* prev, Node* next);
    virtual ~Node();
    
    Node* prev() const;
    Node* next() const;
    T& value();

    bool operator==(const Node& other) const;
    bool operator!=(const Node& other) const;
  };
  
private:
  LinkedList<T>::Node* mhead;
  LinkedList<T>::Node* mlast;
  int mcount;

public:
  LinkedList();
  virtual ~LinkedList();

  int count();
  LinkedList<T>::Node* head();
  LinkedList<T>::Node* last();
  
  LinkedList<T>::Node* AddFirst(T value);
  LinkedList<T>::Node* AddLast(T value);
  LinkedList<T>::Node* AddBefore(LinkedList<T>::Node& node, T value);
  LinkedList<T>::Node* AddAfter(LinkedList<T>::Node& node, T value);

  bool Remove(LinkedList<T>::Node* node);
  bool Remove(T value);
  
  bool Contains(LinkedList<T>::Node* node) const;
  LinkedList<T>::Node* Find(T value) const;
  void Clear();
};

template<typename T>
LinkedList<T>::LinkedList() : mcount(0), mhead(nullptr), mlast(nullptr)
{
  
}

template<typename T>
LinkedList<T>::~LinkedList()
{
  Clear();
}

template<typename T>
int LinkedList<T>::count()
{ return mcount; }

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::head()
{ return mhead; }

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::last()
{ return mlast; }

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::AddFirst(T value)
{
  mcount++;
  
  if (mhead == nullptr) {
    mhead = new LinkedList<T>::Node(value, nullptr, nullptr);
    mlast = mhead;
    return mhead;;
  }
  LinkedList<T>::Node* newNode = new LinkedList<T>::Node(value, nullptr, mhead);
  mhead->mprev = newNode;
  mhead = newNode;
  return newNode;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::AddLast(T value)
{
  mcount++;
  
  if (mhead == nullptr) {
    mhead = new LinkedList<T>::Node(value, nullptr, nullptr);
    mlast = mhead;
    return mhead;
  }
  LinkedList<T>::Node* newNode = new LinkedList<T>::Node(value, mlast, nullptr);
  mlast->mnext = newNode;
  mlast = newNode;
  return mlast;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::AddBefore(LinkedList<T>::Node& node, T value)
{
  if (Contains(&node) == false) {
    throw std::invalid_argument("Node is not in the list");
  }
  mcount++;
  
  LinkedList<T>::Node* newNode = new LinkedList<T>::Node(value, node.mprev, &node);
  if (node.mprev)
    node.mprev->mnext = newNode;
  node.mprev = newNode;

  if (node == *mhead)
    mhead = newNode;

  return newNode;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::AddAfter(LinkedList<T>::Node& node, T value)
{
  if (Contains(&node) == false) {
    throw std::invalid_argument("Node is not in the list");
  }
  mcount++;
  
  LinkedList<T>::Node* newNode = new LinkedList<T>::Node(value, &node, node.mnext);
  if (node.mnext)
    node.mnext->mprev = newNode;
  node.mnext = newNode;

  if (node == *mlast)
    mlast = newNode;

  return newNode;
}

template<typename T>
bool LinkedList<T>::Remove(LinkedList<T>::Node* node)
{
  if (!node)
    throw std::invalid_argument("Can't remove node. node is invalid");

  return Remove(node->mvalue);
}

template<typename T>
bool LinkedList<T>::Remove(T value)
{
  LinkedList<T>::Node* node = Find(value);
  if (!node) return false;
  
  mcount--;
  
  if (node->mprev)
    node->mprev->mnext = node->mnext;
  if (node->mnext) 
    node->mnext->mprev = node->mprev;

  if (node == mhead)
    mhead = mhead->mnext;

  if (node == mlast)
    mlast = mlast->mprev;

  node->mprev = nullptr;
  node->mnext = nullptr;
  delete node;
  node = nullptr;
  return true;
}

template<typename T>
bool LinkedList<T>::Contains(LinkedList<T>::Node* node) const
{
  if (!node)
    throw std::invalid_argument("Contains: node is invalid");
  auto current = mhead;
  while (current != nullptr) {
    if (current == node) {
      return true;
    }
    current = current->mnext;
  }
  return false;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(T value) const
{
  LinkedList<T>::Node* current = mhead;
  while (current != nullptr) {
    if (current->mvalue == value) {
      return current;
    }

    current = current->mnext;
  }
  return nullptr;
}

template<typename T>
void LinkedList<T>::Clear()
{
  LinkedList<T>::Node* current = mhead;
  while (current != nullptr) {
    auto tmp = current->mnext;
    delete current;
    current = nullptr;
    current = tmp;
  }

  mhead = nullptr;
  mlast = nullptr;
  mcount = 0;
}

// Node
template<typename T>
LinkedList<T>::Node::Node(T value, Node* prev, Node* next) : mvalue(std::move(value)), mprev(prev), mnext(next)
{
    
}

template<typename T>
LinkedList<T>::Node::~Node()
{
  // TODO: Node Destructor
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Node::prev() const
{ return mprev; }

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Node::next() const
{ return mnext; }

template<typename T>
T& LinkedList<T>::Node::value()
{ return mvalue; }

template<typename T>
bool LinkedList<T>::Node::operator==(const LinkedList<T>::Node &other) const
{
  return mvalue == other.mvalue && mprev == other.mprev && mnext == other.mnext;
}

template<typename T>
bool LinkedList<T>::Node::operator!=(const LinkedList<T>::Node &other) const
{
  return !((*this) == other);
}
