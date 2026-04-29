#pragma once

#include "vec3.hpp"
#include <limits>

#include "hittable.hpp"

struct Triangle : public Hittable
{
  Point3 a, b, c;

  Triangle(Point3 a, Point3 b, Point3 c) : a(a), b(b), c(c) {}

  bool hit(const Ray& r, Interval ray_t, Hit_Record& rec) const override
  {
    constexpr float epsilon = 1e-6;

    Vec3 edge1 = b - a;
    Vec3 edge2 = c - a;

    // backface culling, assuming CCW-wound triangles.
    const Vec3 normal = cross(edge1, edge2); // no need to normalize
    //if (dot(normal, r.direction()) > 0) return false;

    Vec3 ray_cross_e2 = cross(r.direction(), edge2);
    float det = dot(edge1, ray_cross_e2);

    if (abs(det) < epsilon) return false; // ray is parallel to triangle

    float inv_det = 1.0 / det;
    Point3 s = r.origin() - a;
    float u = inv_det * dot(s, ray_cross_e2);
    // ray passes outside edge2's bounds
    if (u < - epsilon || u > 1.0 + epsilon) return false;

    Vec3 s_cross_e1 = cross(s, edge1);
    float v = inv_det * dot(r.direction(), s_cross_e1);

    // ray passes outside edge1's bounds
    if (v < - epsilon || u + v > 1.0 + epsilon) return false;

    // the ray line intersects with the triangle
    // we compute t to find where on the ray the intersection is
    float t = inv_det * dot(edge2, s_cross_e1);

    if (!ray_t.contains(t)) {
      return false;
    }

    //rec.normal = normal;
    rec.t = t;
    rec.p = r.at(t);
    rec.set_face_normal(r, unit_vector(normal));

    return true; // ray intersection
  }
};


