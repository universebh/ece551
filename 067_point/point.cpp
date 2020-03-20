#include "point.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <cmath>

double & Point::getX() {
  return x;
}

double & Point::getY() {
  return y;
}

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
}
