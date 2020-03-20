#include "node.h"
void Node::buildMap(Node * nd, BitString b, std::map<unsigned, BitString> & theMap) {
  if (nd->sym != NO_SYM) {
    assert(nd->left == NULL && nd->right == NULL);
    theMap.insert(std::pair<unsigned, BitString>(nd->sym, b));
  }
  else {
    assert(nd->left != NULL && nd->right != NULL);
    buildMap(nd->left, b.plusZero(), theMap);
    buildMap(nd->right, b.plusOne(), theMap);
  }
}

void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  buildMap(this, b, theMap);
}
