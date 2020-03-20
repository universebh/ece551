// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!

//Code starts

#include <stdio.h>
#include <stdlib.h>

struct dim2_tag {
  int x;
  int y;
};
typedef struct dim2_tag dim2_t;

struct dim2range_tag {
  int xLow;
  int xHi;
  int yLow;
  int yHi;
};
typedef struct dim2range_tag dim2range_t;

int seq3(int x, int y) {
  int fx0 = 0 + (-3) * (x - 0);
  int dx = 2 + 1 * (x - 0);
  int dxy = fx0 + dx * (y - 0);
  return dxy;
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  if (xLow >= xHi || yLow >= yHi) {
    return 0;
  }
  int count = 0;
  for (int i = xLow; i < xHi; i++) {
    for (int j = yLow; j < yHi; j++) {
      if (seq3(i, j) % 2 == 0) {
        count++;
      }
    }
  }
  return count;
}

int main() {
  dim2_t p1 = {0, 0};
  dim2_t p2 = {3, 0};
  dim2_t p3 = {-5, 0};
  dim2_t p4 = {0, 2};
  dim2_t p5 = {0, -4};
  dim2_t p6 = {1, 2};
  dim2_t p7 = {2, -4};
  dim2_t p8 = {-3, 5};
  dim2_t p9 = {-5, -5};
  printf("seq3(%d, %d) = %d\n", p1.x, p1.y, seq3(p1.x, p1.y));
  printf("seq3(%d, %d) = %d\n", p2.x, p2.y, seq3(p2.x, p2.y));
  printf("seq3(%d, %d) = %d\n", p3.x, p3.y, seq3(p3.x, p3.y));
  printf("seq3(%d, %d) = %d\n", p4.x, p4.y, seq3(p4.x, p4.y));
  printf("seq3(%d, %d) = %d\n", p5.x, p5.y, seq3(p5.x, p5.y));
  printf("seq3(%d, %d) = %d\n", p6.x, p6.y, seq3(p6.x, p6.y));
  printf("seq3(%d, %d) = %d\n", p7.x, p7.y, seq3(p7.x, p7.y));
  printf("seq3(%d, %d) = %d\n", p8.x, p8.y, seq3(p8.x, p8.y));
  printf("seq3(%d, %d) = %d\n", p9.x, p9.y, seq3(p9.x, p9.y));

  dim2range_t r1 = {0, 2, 0, 3};
  dim2range_t r2 = {-1, -2, -2, 1};
  dim2range_t r3 = {-1, 2, -2, 1};
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         r1.xLow,
         r1.xHi,
         r1.yLow,
         r1.yHi,
         countEvenInSeq3Range(r1.xLow, r1.xHi, r1.yLow, r1.yHi));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         r2.xLow,
         r2.xHi,
         r2.yLow,
         r2.yHi,
         countEvenInSeq3Range(r2.xLow, r2.xHi, r2.yLow, r2.yHi));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         r3.xLow,
         r3.xHi,
         r3.yLow,
         r3.yHi,
         countEvenInSeq3Range(r3.xLow, r3.xHi, r3.yLow, r3.yHi));

  return EXIT_SUCCESS;
}

//Code ends
