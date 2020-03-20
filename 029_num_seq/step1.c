// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq1(int x) {
  return 3 * x + (-3 + (x - 0));
}

void printSeq1Range(int low, int high) {
  // assert(low <= high);
  if (low >= high) {
    printf("\n");
    return;
  }
  printf("%d", seq1(low));
  if (low < high - 1) {
    printf(", ");
  }
  printSeq1Range((low + 1), high);
}

int main() {
  int x1 = 0;
  int x2 = 1;
  int x3 = 5;
  int x4 = 8;
  int x5 = -1;
  int x6 = -3;
  int x7 = -4;
  printf("seq1(%d) = %d\n", x1, seq1(x1));
  printf("seq1(%d) = %d\n", x2, seq1(x2));
  printf("seq1(%d) = %d\n", x3, seq1(x3));
  printf("seq1(%d) = %d\n", x4, seq1(x4));
  printf("seq1(%d) = %d\n", x5, seq1(x5));
  printf("seq1(%d) = %d\n", x6, seq1(x6));
  printf("seq1(%d) = %d\n", x7, seq1(x7));

  int low1 = 0;
  int high1 = 0;
  int low2 = 0;
  int high2 = 4;
  int low3 = -2;
  int high3 = 6;
  int low4 = 7;
  int high4 = 3;
  printf("printSeq1Range(%d, %d)\n", low1, high1);
  printSeq1Range(low1, high1);
  printf("printSeq1Range(%d, %d)\n", low2, high2);
  printSeq1Range(low2, high2);
  printf("printSeq1Range(%d, %d)\n", low3, high3);
  printSeq1Range(low3, high3);
  printf("printSeq1Range(%d, %d)\n", low4, high4);
  printSeq1Range(low4, high4);

  return EXIT_SUCCESS;
}
