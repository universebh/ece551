#include "circle.h"

#include <ctype.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#define PI 3.1415926535

using std::cout;
using std::endl;

Circle::Circle(Point p, double r) : point(p), radius(r) {}

void Circle::move(double dx, double dy) {
  point.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  if (this == &otherCircle) {
    return PI * pow(radius, 2);
  }
  double d = point.distanceFrom(otherCircle.point);
  if (d < radius + otherCircle.radius) {
    double rsqr1 = pow(radius, 2);
    double rsqr2 = pow(otherCircle.radius, 2);
    if (d < abs(radius - otherCircle.radius)) {
      return PI * fmin(rsqr1, rsqr2);
    }
    double dsqr = pow(d, 2);
    double semiTheta1 = acos((dsqr + rsqr1 - rsqr2) / (2 * d * radius));
    double semiTheta2 = acos((dsqr + rsqr2 - rsqr1) / (2 * d * otherCircle.radius));
    double semiFanShapeArea = 0.5 * semiTheta1 * rsqr1 + 0.5 * semiTheta2 * rsqr2;
    double p = (d + radius + otherCircle.radius) / 2;
    double overlapTriArea = sqrt(p * (p - d) * (p - radius) * (p - otherCircle.radius));
    double semiArea = semiFanShapeArea - overlapTriArea;
    return 2 * semiArea;
  }
  return 0;
}
