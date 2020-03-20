//Start of code
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    printf("Error occoured at x = %d, y = %d\n", x, y);
    exit(EXIT_FAILURE);
  }
}

int main() {
  unsigned int x1 = 2;
  unsigned int y1 = 3;
  run_check(x1, y1, 8);

  unsigned int x2 = 0;
  unsigned int y2 = 2;
  run_check(x2, y2, 0);

  unsigned int x3 = 2;
  unsigned int y3 = 0;
  run_check(x3, y3, 1);

  unsigned int x4 = 5000;
  unsigned int y4 = 2;
  run_check(x4, y4, 25000000);

  unsigned int x5 = 100;
  unsigned int y5 = 2;
  run_check(x5, y5, 10000);

  unsigned int x6 = 0;
  unsigned int y6 = 0;
  run_check(x6, y6, 1);

  return EXIT_SUCCESS;
}

//End of code
