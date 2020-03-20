#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

class Point
{
 private:
  double x;
  double y;

 public:
  Point() : x(0), y(0){};
  double & getX();
  double & getY();
  void move(double dx, double dy);
  double distanceFrom(const Point & p);
};
