//Code starts

#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n <= 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  int count = 1;
  int ans = count;
  for (size_t i = 0; i < n - 1; i++) {
    if (array[i + 1] > array[i]) {
      count++;
    }
    else {
      count = 1;
    }
    if (count > ans) {
      ans = count;
    }
  }
  return ans;
}

//Code ends
