#include <ctype.h>

#include <cstdio>
#include <cstdlib>

#include "point.h"

class Circle
{
 private:
  Point point;
  const double radius;

 public:
  Circle(Point p, double r);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCirle);
};
