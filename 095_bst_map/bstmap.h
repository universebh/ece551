#ifndef __BSTMAP_H__
#define __BSTMAP_H__

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "map.h"

using std::cerr;
using std::cout;
using std::endl;

template<typename K, typename V>
class BstMap : public Map<K, V>
{
 private:
  class Node
  {
   public:
    K key;
    V value;
    Node * left;
    Node * right;

   public:
    Node() : key(), value(), left(NULL), right(NULL) {}
    Node(K k, V v) : key(k), value(v), left(NULL), right(NULL) {}
  };
  Node * root;

  void copy(Node * curr);
  void destroy(Node * curr);

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap<K, V> & rhs);
  BstMap & operator=(const BstMap<K, V> & rhs);
  virtual void add(const K & k, const V & v);
  virtual const V & lookup(const K & k) const throw(std::invalid_argument);
  virtual void remove(const K & k);
  virtual ~BstMap();
  //checkings
  template<typename G, typename W>
  friend class TestBstMap;
};

template<typename G, typename W>
class TestBstMap
{
 private:
  size_t nodeNum;

  void checkNodes(typename BstMap<G, W>::Node * curr, const G * k, const W * v) {
    if (curr != NULL) {
      checkNodes(curr->left, k, v);
      if (k[nodeNum] != curr->key || v[nodeNum] != curr->value) {
        cerr << "bst(" << curr->key << ", " << curr->value << ") ";
        cerr << "!= (" << k[nodeNum] << ", " << v[nodeNum] << ") ";
        cerr << "@ Node #" << nodeNum << endl;
        throw std::exception();
      }
      nodeNum++;
      checkNodes(curr->right, k, v);
    }
  }

 public:
  TestBstMap() : nodeNum(0) {}
  virtual void checkNodes(const BstMap<G, W> & bst, const G * k, const W * v, size_t n) {
    nodeNum = 0;
    checkNodes(bst.root, k, v);
    if (nodeNum != n) {
      cerr << "number of nodes not match [bst, real] = (";
      cerr << nodeNum << ", " << n << ")" << endl;
      throw std::exception();
    }
    cout << "nodes clear" << endl;
  }
};

template<typename K, typename V>
void BstMap<K, V>::copy(Node * curr) {
  if (curr != NULL) {
    this->add(curr->key, curr->value);
    copy(curr->left);
    copy(curr->right);
  }
}

template<typename K, typename V>
BstMap<K, V>::BstMap(const BstMap<K, V> & rhs) : root(NULL) {
  copy(rhs.root);
}

template<typename K, typename V>
BstMap<K, V> & BstMap<K, V>::operator=(const BstMap<K, V> & rhs) {
  if (this != &rhs) {
    BstMap<K, V> temp(rhs);
    std::swap(root, temp.root);
  }
  return *this;
}

template<typename K, typename V>
void BstMap<K, V>::add(const K & k, const V & v) {
  Node ** curr = &root;
  while (*curr != NULL) {
    if (k < (*curr)->key) {
      curr = &(*curr)->left;
    }
    else if (k > (*curr)->key) {
      curr = &(*curr)->right;
    }
    else {
      (*curr)->value = v;
      return;
    }
  }
  *curr = new Node(k, v);
}

template<typename K, typename V>
const V & BstMap<K, V>::lookup(const K & k) const throw(std::invalid_argument) {
  Node * curr = root;
  while (curr != NULL) {
    if (k == curr->key) {
      return curr->value;
    }
    else if (k < curr->key) {
      curr = curr->left;
    }
    else {
      curr = curr->right;
    }
  }
  std::stringstream ss;
  ss << "cannot find the key(" << k << ")";
  std::string msg = ss.str();
  throw std::invalid_argument(msg);
}

template<typename K, typename V>
void BstMap<K, V>::remove(const K & k) {
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

template<typename K, typename V>
void BstMap<K, V>::destroy(Node * curr) {
  if (curr != NULL) {
    destroy(curr->left);
    destroy(curr->right);
    delete curr;
    curr = NULL;
  }
}

template<typename K, typename V>
BstMap<K, V>::~BstMap() {
  destroy(root);
}

#endif
