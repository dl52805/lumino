#pragma once

#include "ray.hpp"

struct Hit_Record
{
  Point3 p;
  Vec3 normal;
  double t;
  bool front_face;

  void set_face_normal(const Ray& r, const Vec3& outward_normal)
  {
    front_face = dot(r.direction(), outward_normal);
    normal = front_face ? outward_normal : - outward_normal;
  }
};

struct Hittable
{
  virtual ~Hittable() = default;
  virtual bool hit(const Ray& r, double ray_tmin,
    double ray_tmax, Hit_Record& rec) const = 0;
};


