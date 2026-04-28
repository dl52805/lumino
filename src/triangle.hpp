#pragma once

#include "vec3.hpp"
#include <limits>

struct Triangle
{
  Point3 a, b, c;

  Triangle(Point3 a, Point3 b, Point3 c) : a(a), b(b), c(c) {}

  bool ray_intersects_triangle( const Point3 &ray_origin,
    const Point3 &ray_vector)
  {
    constexpr float epsilon = std::numeric_limits<float>::epsilon();

    Point3 edge1 = b - a;
    Point3 edge2 = c - a;

    // Backface culling, assuming CCW-wound triangles.
    const Point3 normal = cross(edge1, edge2); // No need to normalize
    if (dot(normal, ray_vector) > 0) {
      return false;
    }

    Point3 ray_cross_e2 = cross(ray_vector, edge2);
    float det = dot(edge1, ray_cross_e2);

    if (abs(det) < epsilon) {
      return false; // Ray is parallel to triangle
    }

    float inv_det = 1.0 / det;
    Point3 s = ray_origin - a;
    float u = inv_det * dot(s, ray_cross_e2);
    // Ray passes outside edge2's bounds
    if (u < -epsilon || u - 1 > epsilon) {
      return false;
    }

    Point3 s_cross_e1 = cross(s, edge1);
    float v = inv_det * dot(ray_vector, s_cross_e1);

    // Ray passes outside edge1's bounds
    if (v < -epsilon || u + v - 1 > epsilon) {
      return false;
    }

    // The ray line intersects with the triangle.
    // We compute t to find where on the ray the intersection is.
    float t = inv_det * dot(edge2, s_cross_e1);

    if (t > epsilon) // Ray intersection
    {
      return  true;
    }
    else {
      return false;
    }
  }
};

