#include <cassert>
#include <cstdlib>
#include <exception>
#include <iostream>

#include "il.h"

using namespace std;

void testCstr(void) {
  //check constructor
  cout << "checking constructor" << endl;
  IntList lst;
  assert(lst.head == NULL && lst.tail == NULL && lst.size == 0);
  cout << "constructor clear" << endl;
}

void testPtr(const IntList & lst) {
  //check pointers
  cout << "checking pointers" << endl;
  assert(lst.head->prev == NULL && lst.tail->next == NULL);
  int i = 0;
  IntList::Node * curr = lst.head;
  while (curr != NULL) {
    if (curr->next != NULL) {
      assert(curr->next->prev == curr);
    }
    curr = curr->next;
    i++;
    //cout << i << endl;
  }
  assert(i == lst.size);
  cout << "pointers clear" << endl;
}

void testVal(const IntList & lst, int val[]) {
  cout << "checking values" << endl;
  int i = 0;
  IntList::Node * curr = lst.head;
  while (curr != NULL) {
    assert(curr->data == val[i]);
    curr = curr->next;
    i++;
  }
  cout << "values clear" << endl;
}

void testAdds(void) {
  cout << "checking adds" << endl;
  //check addFront() and addBack()
  IntList lst;
  lst.addFront(1);
  lst.addBack(2);
  lst.addFront(-3);
  int val[3] = {-3, 1, 2};
  assert(lst.head != NULL && lst.tail != NULL);
  testPtr(lst);
  testVal(lst, val);
  cout << "adds clear" << endl;
}

void testCpCstr(void) {
  //check copy constructor
  cout << "checking copy constructor" << endl;
  IntList lst1;
  lst1.addFront(4);
  lst1.addFront(3);
  IntList lst2(lst1);
  assert(lst2.head != lst1.head && lst2.tail != lst1.tail && lst1.size == 2 &&
         lst2.size == lst1.size);
  cout << "copy constructor clear" << endl;
}

void testAsmOp(void) {
  //check assignment operator
  cout << "chekcing assignment operator" << endl;
  IntList lst1;
  lst1.addFront(3);
  lst1.addBack(4);
  IntList lst2;
  lst2.addFront(-1);
  lst2 = lst1;
  assert(lst1.head != lst2.head && lst1.tail != lst2.tail && lst1.size == 2 &&
         lst1.size == lst2.size);
  int val[2] = {3, 4};
  testPtr(lst2);
  testVal(lst2, val);
  cout << "assignment operator clear" << endl;
}

void testRm(void) {
  cout << "checking remove" << endl;
  IntList lst;
  //check remove from a empty list
  bool rmRlt0 = lst.remove(0);
  assert(rmRlt0 == false && lst.size == 0);

  lst.addFront(1);
  lst.addBack(2);
  lst.addFront(-3);
  //check remove() a non-exist number
  bool rmRlt1 = lst.remove(-10);
  assert(rmRlt1 == false && lst.size == 3);
  //check remove() a exisited number
  bool rmRlt2 = lst.remove(-3);
  assert(rmRlt2 == true);
  int val[2] = {1, 2};
  assert(lst.head != NULL && lst.tail != NULL & lst.size == 2);
  testPtr(lst);
  testVal(lst, val);
  //check remove form a unit list
  IntList unit;
  unit.addBack(1);
  unit.remove(1);
  assert(unit.head == NULL && unit.tail == NULL);

  cout << "remove clear" << endl;
}

void testIdxOp(void) {
  //check [] operator
  cout << "checking index opertor" << endl;
  //empty list
  IntList lst;
  lst.addBack(1);
  lst.addBack(2);
  lst.addBack(3);
  lst[1] = 10;
  int val[3] = {1, 10, 3};
  for (int i = 0; i < lst.size; i++) {
    assert(lst[i] == val[i]);
  }
  cout << "index operator clear" << endl;
}

void testCstIdxOp(void) {
  //check const [] operator
  cout << "checking const index operator" << endl;
  IntList lst;
  lst.addBack(1);
  lst.addBack(2);
  lst.addBack(3);
  const int val[3] = {1, 2, 3};
  for (int i = 0; i < lst.size; i++) {
    const int a = lst[i];
    assert(a == val[i]);
  }
  cout << "const index operator clear" << endl;
}

void testFind(void) {
  //check find()
  cout << "checking find" << endl;
  //empty list
  IntList empty;
  assert(empty.find(1) == -1);
  IntList lst;
  lst.addBack(1);
  lst.addBack(-5);
  lst.addBack(2);
  //non-exist item
  assert(lst.find(10) == -1);
  //others
  int val[3] = {1, -5, 2};
  for (int i = 0; i < lst.size; i++) {
    assert(lst.find(val[i]) == i);
  }
  cout << "find clear" << endl;
}

void testGetSz(void) {
  //check GetSize()
  cout << "checking get size" << endl;
  IntList lst;
  for (int i = 0; i < 5; i++) {
    assert(lst.getSize() == i);
    lst.addBack(i);
  }
  cout << "git size clear" << endl;
}

void testList(void) {
  testCstr();
  testAdds();
  testCpCstr();
  testAsmOp();
  testRm();
  testIdxOp();
  testCstIdxOp();
  testFind();
  testGetSz();
}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}
