#pragma once

#include "ray.hpp"

struct Hit_Record
{
  Point3 p;
  Vec3 normal;
  double t;
};

struct Hittable
{
  virtual ~Hittable() = default;
  virtual bool hit(const Ray& r, double ray_tmin,
    double ray_tmax, Hit_Record& rec) const = 0;
};


