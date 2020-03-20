#include "bstset.h"
#include "set.h"

void testCase1() {
  BstSet<int> bss;
  TestBstSet<int> tss;
  int addKey[] = {35, 15, 7, 26, 49, 58};
  int chkKey[] = {7, 15, 26, 35, 49, 58};
  for (int i = 0; i < 6; i++) {
    bss.add(addKey[i]);
  }
  tss.checkNodes(bss, chkKey, 6);
  BstSet<int> bss2(bss);
  tss.checkNodes(bss2, chkKey, 6);
  try {
    bss.contains(0);
  }
  catch (std::invalid_argument & e) {
    cerr << e.what() << endl;
  }
  for (int i = 0; i < 6; i++) {
    bool kk = bss2.contains(addKey[i]);
    if (kk != true) {
      cerr << "contains doesn't match" << endl;
      throw std::exception();
    }
  }
  cout << "contains matches" << endl;
  int remvKey2[] = {7, 35, 49, 58, 26, 15};
  int remvKeySpan2[][6] = {
      //{7, 15, 26, 35, 49, 58},
      {15, 26, 35, 49, 58},
      {15, 26, 49, 58},
      {15, 26, 58},
      {15, 26},
      {15},
  };
  bss2.remove(100);
  for (int i = 0; i < 6; i++) {
    bss2.remove(remvKey2[i]);
    if (i == 5) {
      tss.checkNodes(bss2, NULL, 0);
    }
    else {
      tss.checkNodes(bss2, remvKeySpan2[i], 6 - i - 1);
    }
  }
}

void testCase2() {
  BstSet<int> bss;
  TestBstSet<int> tss;
  int * key0 = NULL;
  tss.checkNodes(bss, key0, 0);
  bss.remove(10);
  tss.checkNodes(bss, key0, 0);
  bss.add(3);
  bss.remove(3);
  tss.checkNodes(bss, key0, 0);
  int addKey[] = {60, 11, 4, 1, 25, 11, 21, 35, 93, 84, 70, 86};
  int chkKey[] = {1, 4, 11, 21, 25, 35, 60, 70, 84, 86, 93};
  for (int i = 0; i < 12; i++) {
    bss.add(addKey[i]);
  }
  tss.checkNodes(bss, chkKey, 11);
  BstSet<int> bss2(bss);
  bss.remove(11);
  int key2[] = {1, 4, 21, 25, 35, 60, 70, 84, 86, 93};
  tss.checkNodes(bss, key2, 10);
  bss.remove(84);
  int key3[] = {1, 4, 21, 25, 35, 60, 70, 86, 93};
  tss.checkNodes(bss, key3, 9);
  bss2 = bss;
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
  for (int i = 0; i < 9; i++) {
    bss2.remove(remvKey2[i]);
    if (i == 8) {
      tss.checkNodes(bss2, NULL, 0);
    }
    else {
      tss.checkNodes(bss2, remvKeySpan2[i], 9 - i - 1);
    }
  }
  tss.checkNodes(bss, key3, 9);
}

int main() {
  testCase1();
  testCase2();
  return EXIT_SUCCESS;
}
