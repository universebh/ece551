#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>

using namespace std;

//YOUR CODE GOES HERE

template<typename T>
class LinkedList
{
 private:
  class Node
  {
   public:
    T data;
    Node * next;
    Node * prev;

   public:
    Node() : data(), next(NULL), prev(NULL) {}
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList<T> & rhs);
  ~LinkedList();
  LinkedList<T> operator=(const LinkedList<T> & rhs);
  void addFront(const T & item);
  void addBack(const T & item);
  bool remove(const T & item);
  T & operator[](int index);
  const T & operator[](int index) const;
  int find(const T & item);
  int getSize() const;
  friend void testNodes(const LinkedList<int> & lst, int * val);
};

void testNodes(const LinkedList<int> & lst, int * val) {
  cout << "checking nodes" << endl;
  if (lst.head == NULL) {
    assert(lst.tail == NULL);
  }
  else {
    assert(lst.head->prev == NULL && lst.tail->next == NULL);
  }
  int i = 0;
  typename LinkedList<int>::Node * curr = lst.head;
  while (curr != NULL) {
    if (curr->next != NULL) {
      assert(curr->next->prev == curr);
    }
    assert(curr->data == val[i]);
    curr = curr->next;
    i++;
  }
  assert(i == lst.size);
  if (lst.size == 0) {
    assert(lst.head == NULL && lst.tail == NULL);
  }
  cout << "nodes clear" << endl;
}

/********************************* member functions  ***********************************/

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> & rhs) : head(NULL), tail(NULL), size(0) {
  Node * curr = rhs.head;
  while (curr != NULL) {
    addBack(curr->data);
    curr = curr->next;
  }
}

template<typename T>
LinkedList<T>::~LinkedList() {
  while (head != NULL) {
    Node * temp = head->next;
    delete head;
    head = temp;
    size--;
  }
  tail = NULL;
}

template<typename T>
LinkedList<T> LinkedList<T>::operator=(const LinkedList<T> & rhs) {
  if (this != &rhs) {
    while (head != NULL) {
      Node * t = head->next;
      delete head;
      head = t;
      size--;
    }
    tail = NULL;
    assert(size == 0);
    LinkedList temp(rhs);
    std::swap(size, temp.size);
    std::swap(head, temp.head);
    std::swap(tail, temp.tail);
  }
  return *this;
}

template<typename T>
void LinkedList<T>::addFront(const T & item) {
  Node * temp = new Node();
  temp->data = item;
  temp->next = head;
  temp->prev = NULL;
  head = temp;
  if (tail == NULL) {
    tail = head;
  }
  else {
    head->next->prev = head;
  }
  size++;
}

template<typename T>
void LinkedList<T>::addBack(const T & item) {
  Node * temp = new Node();
  temp->data = item;
  temp->next = NULL;
  temp->prev = tail;
  tail = temp;
  if (head == NULL) {
    head = tail;
  }
  else {
    tail->prev->next = tail;
  }
  size++;
}

template<typename T>
bool LinkedList<T>::remove(const T & item) {
  Node ** curr = &head;
  bool isFound = false;
  while (*curr != NULL) {
    if ((*curr)->data != item) {
      curr = &((*curr)->next);
    }
    else {
      isFound = true;
      break;
    }
  }
  if (isFound) {
    Node * tempNxt = (*curr)->next;
    Node * tempPrv = (*curr)->prev;
    bool changeHead = false;
    if (*curr == head) {
      changeHead = true;
    }
    if (*curr == tail) {
      tail = tempPrv;
    }
    delete *curr;
    if (changeHead) {
      head = tempNxt;
    }
    size--;
    *curr = tempNxt;
    if (tempNxt != NULL) {
      tempNxt->prev = tempPrv;
    }
  }
  return isFound;
}

template<typename T>
T & LinkedList<T>::operator[](int index) {
  if (index < 0 || index >= size) {
    throw std::exception();
  }
  Node * curr = head;
  int i = 0;
  while (curr != NULL && i < index) {
    curr = curr->next;
    i++;
  }
  return curr->data;
}

template<typename T>
const T & LinkedList<T>::operator[](int index) const {
  if (index < 0 || index >= size) {
    throw std::exception();
  }
  Node * curr = head;
  int i = 0;
  while (curr != NULL && i < index) {
    curr = curr->next;
    i++;
  }
  return curr->data;
}

template<typename T>
int LinkedList<T>::find(const T & item) {
  Node * curr = head;
  int i = 0;
  while (curr != NULL) {
    if (curr->data == item) {
      return i;
    }
    curr = curr->next;
    i++;
  }
  return -1;
}

template<typename T>
int LinkedList<T>::getSize() const {
  return size;
}

#endif
