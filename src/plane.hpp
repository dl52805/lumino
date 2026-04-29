#pragma once

#include "vec3.hpp"
#include "ray.hpp"

struct Plane
{
  double a, b, c, d;

  Plane(double a, double b, double c, double d) : a(a), b(b), c(c), d(d) {}

  Point3 ray_intersection(const Ray& r)
  {
    double temp = d - a * r.o.x() - b * r.o.y() - c * r.o.z();
    double temp2 = a * r.dir.x() + b * r.dir.y() + c * r.dir.z();
    double t = temp / temp2;
    Point3 intersection = Point3(
      r.o.x() + t * r.dir.x(),
      r.o.y() + t * r.dir.y(),
      r.o.z() + t * r.dir.z()
    );
    return intersection;
  }
};

