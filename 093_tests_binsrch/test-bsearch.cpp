#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "function.h"

#define N 4
#define BUFFER_SIZE 64

using std::cerr;
using std::cout;
using std::endl;

void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  assert(low <= high);
  int maxInvoke;
  if (high > low) {
    maxInvoke = int(log2(double(high - low))) + 1;
  }
  else {
    maxInvoke = 1;
  }
  Function<int, int> * countFn = new CountedIntFn(maxInvoke, f, mesg);
  int ans = binarySearchForZero(countFn, low, high);
  //cout << "ans = " << ans << endl;
  if (ans != expected_ans) {
    cerr << "The answer is not correct in " << mesg << endl;
    throw std::exception();
  }
  delete countFn;
  countFn = NULL;
}

int main() {
  Function<int, int> * fn[N];
  fn[0] = new SinFuction();
  fn[1] = new SquareFunction();
  fn[2] = new LinearFunction();
  fn[3] = new LinearFunction();
  int info[N][3] = {{0, 150000, 52359}, {1, 1000, 1}, {-10, -10, -10}, {-3, 4, -1}};
  char mesg[N][BUFFER_SIZE];
  strcpy(mesg[0], "SinFunction[0, 150000)");
  strcpy(mesg[1], "SquareFunction[1, 1000)");
  strcpy(mesg[2], "LinearFunction[-10, -10)");
  strcpy(mesg[3], "LinearFunction[-3, 4)");
  for (int i = 0; i < N; i++) {
    check(fn[i], info[i][0], info[i][1], info[i][2], mesg[i]);
    if (fn[i] != NULL) {
      delete fn[i];
      fn[i] = NULL;
    }
  }
  return (EXIT_SUCCESS);
}
