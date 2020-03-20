#include <cstdlib>
#include <iostream>

#include "ll.h"

using namespace std;

int main() {
  //copy constr
  //assi constr
  LinkedList<int> lst1;
  lst1.addBack(1);
  lst1.addBack(-2);
  LinkedList<int> lst2(lst1);
  lst2.addFront(3);
  LinkedList<int> lst3(lst2);
  lst3 = lst1;
  int val1[] = {1, -2};
  int val2[] = {3, 1, -2};
  int val3[] = {1, -2};
  testNodes(lst1, val1);
  testNodes(lst2, val2);
  testNodes(lst3, val3);
  //remove
  LinkedList<int> lst4(lst3);
  int val4_0[] = {1, -2};
  testNodes(lst4, val4_0);
  assert(lst4.remove(1) == true);
  int val4[] = {-2};
  testNodes(lst4, val4);
  assert(lst4.remove(10) == false);
  int val4_2[] = {-2};
  testNodes(lst4, val4_2);
  assert(lst4.remove(-2) == true);
  int * val4_3 = NULL;
  testNodes(lst4, val4_3);
  //[]
  LinkedList<int> lst5;
  lst5.addBack(1);
  lst5.addBack(3);
  lst5.addBack(5);
  lst5.addBack(7);
  for (int i = 0; i < lst5.getSize(); i++) {
    cout << lst5[i] << "\t";
  }
  cout << endl;
  lst5[2] = 10;
  for (int i = 0; i < lst5.getSize(); i++) {
    cout << lst5[i] << "\t";
  }
  cout << endl;
  //LinkedList<int> lst6;
  //cout << lst6[0] << endl;
  //find
  LinkedList<int> lst6;
  cout << "empty lst6: " << lst6.find(0) << endl;
  lst6.addFront(2);
  lst6.addFront(4);
  lst6.addFront(6);
  int val6[] = {6, 4, 2};
  testNodes(lst6, val6);
  return (EXIT_SUCCESS);
}
