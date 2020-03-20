#include <cassert>

#include "node.h"

Node * buildTree(priority_queue_t & pq) {
  if (pq.size() < 2) {
    return pq.top();
  }
  Node * l = pq.top();
  pq.pop();
  Node * r = pq.top();
  pq.pop();
  Node * nw = new Node(l, r);
  pq.push(nw);
  return buildTree(pq);
}

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;
  for (int i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  if (pq.size() < 1) {
    return NULL;
  }
  return buildTree(pq);
}
