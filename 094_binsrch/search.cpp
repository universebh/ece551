#include <cassert>
#include <cstdlib>
#include <iostream>

#include "function.h"

using std::cout;
using std::endl;

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low >= high - 1) {
    return low;
  }
  int mid = low + (high - low) / 2;
  int fmid = f->invoke(mid);
  if (0 < fmid) {
    return binarySearchForZero(f, low, mid);
  }
  else {
    return binarySearchForZero(f, mid, high);
  }
}
