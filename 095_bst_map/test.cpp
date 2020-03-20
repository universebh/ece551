#include "bstmap.h"
#include "map.h"

void testCase1() {
  BstMap<int, int> bst;
  TestBstMap<int, int> tst;
  int addKey[] = {35, 15, 7, 26, 49, 58};
  int addVal[] = {1, 2, 3, 4, 5, 6};
  int chkKey[] = {7, 15, 26, 35, 49, 58};
  int chkVal[] = {3, 2, 4, 1, 5, 6};
  for (int i = 0; i < 6; i++) {
    bst.add(addKey[i], addVal[i]);
  }
  tst.checkNodes(bst, chkKey, chkVal, 6);
  BstMap<int, int> bst2(bst);
  tst.checkNodes(bst2, chkKey, chkVal, 6);
  try {
    bst.lookup(0);
  }
  catch (std::invalid_argument & e) {
    cerr << e.what() << endl;
  }
  for (int i = 0; i < 6; i++) {
    int kk = bst2.lookup(addKey[i]);
    if (kk != addVal[i]) {
      cerr << "lookup doesn't match" << endl;
      throw std::exception();
    }
  }
  cout << "lookup matches" << endl;
  int remvKey2[] = {7, 35, 49, 58, 26, 15};
  int remvKeySpan2[][6] = {
      //{7, 15, 26, 35, 49, 58},
      {15, 26, 35, 49, 58},
      {15, 26, 49, 58},
      {15, 26, 58},
      {15, 26},
      {15},
  };
  int remvValSpan2[][6] = {
      //{3, 2, 4, 1, 5, 6},
      {2, 4, 1, 5, 6},
      {2, 4, 5, 6},
      {2, 4, 6},
      {2, 4},
      {2},
  };
  bst2.remove(100);
  for (int i = 0; i < 6; i++) {
    bst2.remove(remvKey2[i]);
    if (i == 5) {
      tst.checkNodes(bst2, NULL, NULL, 0);
    }
    else {
      tst.checkNodes(bst2, remvKeySpan2[i], remvValSpan2[i], 6 - i - 1);
    }
  }
}

void testCase2() {
  BstMap<int, int> bst;
  TestBstMap<int, int> tst;
  int * key0 = NULL;
  int * val0 = NULL;
  tst.checkNodes(bst, key0, val0, 0);
  bst.remove(10);
  tst.checkNodes(bst, key0, val0, 0);
  bst.add(3, 10);
  bst.remove(3);
  tst.checkNodes(bst, key0, val0, 0);
  int addKey[] = {60, 11, 4, 1, 25, 11, 21, 35, 93, 84, 70, 86};
  int addVal[] = {1, 2, 3, 4, 5, 33, 6, 7, 8, 9, 10, 11};
  int chkKey[] = {1, 4, 11, 21, 25, 35, 60, 70, 84, 86, 93};
  int chkVal[] = {4, 3, 33, 6, 5, 7, 1, 10, 9, 11, 8};
  for (int i = 0; i < 12; i++) {
    bst.add(addKey[i], addVal[i]);
  }
  tst.checkNodes(bst, chkKey, chkVal, 11);
  BstMap<int, int> bst2(bst);
  bst.remove(11);
  int key2[] = {1, 4, 21, 25, 35, 60, 70, 84, 86, 93};
  int val2[] = {4, 3, 6, 5, 7, 1, 10, 9, 11, 8};
  tst.checkNodes(bst, key2, val2, 10);
  bst.remove(84);
  int key3[] = {1, 4, 21, 25, 35, 60, 70, 86, 93};
  int val3[] = {4, 3, 6, 5, 7, 1, 10, 11, 8};
  tst.checkNodes(bst, key3, val3, 9);
  bst2 = bst;
  int remvKey2[] = {25, 70, 4, 60, 21, 1, 86, 93, 35};
  int remvKeySpan2[][9] = {//{1, 4, 21, 25, 35, 60, 70, 86, 93},
                           {1, 4, 21, 35, 60, 70, 86, 93},
                           {1, 4, 21, 35, 60, 86, 93},
                           {1, 21, 35, 60, 86, 93},
                           {1, 21, 35, 86, 93},
                           {1, 35, 86, 93},
                           {35, 86, 93},
                           {35, 93},
                           {35}};
  int remvValSpan2[][9] = {//{4, 3, 6, 5, 7, 1, 10, 11, 8},
                           {4, 3, 6, 7, 1, 10, 11, 8},
                           {4, 3, 6, 7, 1, 11, 8},
                           {4, 6, 7, 1, 11, 8},
                           {4, 6, 7, 11, 8},
                           {4, 7, 11, 8},
                           {7, 11, 8},
                           {7, 8},
                           {7}};
  for (int i = 0; i < 9; i++) {
    bst2.remove(remvKey2[i]);
    if (i == 8) {
      tst.checkNodes(bst2, NULL, NULL, 0);
    }
    else {
      tst.checkNodes(bst2, remvKeySpan2[i], remvValSpan2[i], 9 - i - 1);
    }
  }
  tst.checkNodes(bst, key3, val3, 9);
}

int main() {
  testCase1();
  testCase2();
  return EXIT_SUCCESS;
}
