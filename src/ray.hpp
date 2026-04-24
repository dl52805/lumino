#pragma once

#include "vec3.hpp"

struct Ray
{
  Point3 o;
  Vec3 dir;

  Ray() {}

  Ray(const Point3& origin, const Vec3& direction)
    : o(origin), dir(direction) {}

  const Point3& origin() const { return this->o; }
  const Vec3& direction() const { return this->dir; }

  Point3 at(double t) const
  {
    return o + t * dir;
  }
};

