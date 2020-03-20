#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <cmath>
#include <cstdlib>
#include <exception>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

template<typename R, typename A>
class Function
{
 public:
  virtual R invoke(A arg) = 0;
  virtual ~Function() {}
};

class CountedIntFn : public Function<int, int>
{
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      cerr << "Too many function in invocations in " << mesg << endl;
      throw std::exception();
    }
    remaining--;
    return f->invoke(arg);
  }
};

int binarySearchForZero(Function<int, int> * f, int low, int high);

//class BinarySearchForZeroFn : public Function<int, int>
//{
//public:
//  virtual int invoke(int arg) {
//  }
//};

class SinFuction : public Function<int, int>
{
 public:
  virtual int invoke(int arg) {
    int y = 10000000 * (sin(arg / 100000.0) - 0.5);
    return y;
  }
};

class SquareFunction : public Function<int, int>
{
  virtual int invoke(int arg) {
    int y = arg * arg;
    return y;
  }
};

class LinearFunction : public Function<int, int>
{
  virtual int invoke(int arg) {
    int y = 2 * arg + 1;
    return y;
  }
};

#endif
