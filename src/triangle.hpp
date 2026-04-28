#pragma once

#include "vec3.hpp"

struct Triangle
{
  Point3 a, b, c;

  Triangle(Point3 a, Point3 b, Point3 c) : a(a), b(b), c(c) {}
};

