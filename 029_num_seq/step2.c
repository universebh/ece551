// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq2(int x) {
  if (x == 0) {
    return 1;
  }
  if (x > 0) {
    return seq2(x - 1) + (4 + 2 * (x - 1));
  }
  else {
    return seq2(x + 1) - (2 + 2 * (x + 1));
  }
}

int sumSeq2_helper(int low, int high, int res) {
  if (low >= high) {
    return res;
  }
  return sumSeq2_helper(low + 1, high, res + seq2(low));
}

int sumSeq2(int low, int high) {
  return sumSeq2_helper(low, high, 0);
}

int main() {
  int x1 = 0;
  int x2 = 1;
  int x3 = 5;
  int x4 = 9;
  int x5 = -1;
  int x6 = -2;
  int x7 = -4;
  printf("seq2(%d) = %d\n", x1, seq2(x1));
  printf("seq2(%d) = %d\n", x2, seq2(x2));
  printf("seq2(%d) = %d\n", x3, seq2(x3));
  printf("seq2(%d) = %d\n", x4, seq2(x4));
  printf("seq2(%d) = %d\n", x5, seq2(x5));
  printf("seq2(%d) = %d\n", x6, seq2(x6));
  printf("seq2(%d) = %d\n", x7, seq2(x7));

  int low1 = 0;
  int high1 = 2;
  int low2 = 3;
  int high2 = 6;
  int low3 = 9;
  int high3 = 7;
  printf("sumSeq2(%d, %d) = %d\n", low1, high1, sumSeq2(low1, high1));
  printf("sumSeq2(%d, %d) = %d\n", low2, high2, sumSeq2(low2, high2));
  printf("sumSeq2(%d, %d) = %d\n", low3, high3, sumSeq2(low3, high3));
  return EXIT_SUCCESS;
}
