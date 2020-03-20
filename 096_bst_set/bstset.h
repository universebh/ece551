#ifndef __BSTSET_H__
#define __BSTSET_H__

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "set.h"

using std::cerr;
using std::cout;
using std::endl;

template<typename T>
class BstSet : public Set<T>
{
 private:
  class Node
  {
   public:
    T key;
    Node * left;
    Node * right;

    Node() : key(), left(NULL), right(NULL) {}
    Node(T k) : key(k), left(NULL), right(NULL) {}
  };
  Node * root;

  void copy(Node * curr);
  void destroy(Node * curr);

 public:
  BstSet<T>() : root(NULL) {}
  BstSet<T>(const BstSet<T> & rhs);
  BstSet<T> & operator=(const BstSet<T> & rhs);
  virtual void add(const T & k);
  virtual bool contains(const T & k) const;
  virtual void remove(const T & k);
  virtual ~BstSet<T>();
  //checking
  template<typename G>
  friend class TestBstSet;
};

template<typename G>
class TestBstSet
{
 private:
  size_t nodeNum;

  void checkNodes(typename BstSet<G>::Node * curr, const G * k) {
    if (curr != NULL) {
      checkNodes(curr->left, k);
      if (k[nodeNum] != curr->key) {
        std::stringstream ss;
        ss << "bss(" << curr->key << ")"
           << "!="
           << "(" << k[nodeNum] << ")";
        cerr << ss.str() << endl;
        throw std::exception();
      }
      nodeNum++;
      checkNodes(curr->right, k);
    }
  }

 public:
  TestBstSet<G>() : nodeNum(0) {}
  virtual void checkNodes(const BstSet<G> & bss, const G * k, size_t n) {
    nodeNum = 0;
    checkNodes(bss.root, k);
    if (nodeNum != n) {
      std::stringstream ss;
      ss << "number of nodes not match [bss, real] = (" << nodeNum << ", " << n << ")";
      cerr << ss.str() << endl;
      throw std::exception();
    }
    cout << "nodes clear" << endl;
  }
};

template<typename T>
void BstSet<T>::copy(Node * curr) {
  if (curr != NULL) {
    this->add(curr->key);
    copy(curr->left);
    copy(curr->right);
  }
}

template<typename T>
BstSet<T>::BstSet(const BstSet<T> & rhs) : root(NULL) {
  copy(rhs.root);
}

template<typename T>
BstSet<T> & BstSet<T>::operator=(const BstSet<T> & rhs) {
  if (this != &rhs) {
    BstSet<T> temp(rhs);
    std::swap(root, temp.root);
  }
  return *this;
}

template<typename T>
void BstSet<T>::add(const T & k) {
  Node ** curr = &root;
  while (*curr != NULL) {
    if (k < (*curr)->key) {
      curr = &(*curr)->left;
    }
    else if (k > (*curr)->key) {
      curr = &(*curr)->right;
    }
    else {
      return;
    }
  }
  *curr = new Node(k);
}

template<typename T>
bool BstSet<T>::contains(const T & k) const {
  Node * curr = root;
  while (curr != NULL) {
    if (k == curr->key) {
      return true;
    }
    else if (k < curr->key) {
      curr = curr->left;
    }
    else {
      curr = curr->right;
    }
  }
  return false;
}

template<typename T>
void BstSet<T>::remove(const T & k) {
  Node ** curr = &root;
  while (*curr != NULL) {
    if (k < (*curr)->key) {
      curr = &(*curr)->left;
    }
    else if (k > (*curr)->key) {
      curr = &(*curr)->right;
    }
    else {
      if ((*curr)->left == NULL) {
        Node * temp = (*curr)->right;
        delete *curr;
        *curr = temp;
      }
      else if ((*curr)->right == NULL) {
        Node * temp = (*curr)->left;
        delete *curr;
        *curr = temp;
      }
      else {
        Node * prev = *curr;
        Node * temp = (*curr)->right;
        bool goLeft = false;
        while (temp->left != NULL) {
          prev = temp;
          temp = temp->left;
          goLeft = true;
        }
        temp->left = (*curr)->left;
        if (goLeft) {
          prev->left = temp->right;
          temp->right = (*curr)->right;
        }
        delete *curr;
        *curr = temp;
      }
      return;
    }
  }
}

template<typename T>
void BstSet<T>::destroy(Node * curr) {
  if (curr != NULL) {
    destroy(curr->left);
    destroy(curr->right);
    delete curr;
    curr = NULL;
  }
}

template<typename T>
BstSet<T>::~BstSet() {
  destroy(root);
}

#endif
