#pragma once

#include <iostream>

#include "commons.hpp"

#include <fmt/format.h>
#include <fmt/ostream.h>

struct Vec3
{
  double e[3];

  Vec3() : e{0, 0, 0} {}
  Vec3(double e0, double e1, double e2);

  double x() const;
  double y() const;
  double z() const;

  Vec3 operator-() const;
  double operator[](int i) const;
  double& operator[](int i);
  Vec3& operator+=(const Vec3& v);
  Vec3& operator*=(double t);
  Vec3& operator/=(double t);
  double length_squared() const;
  double length() const;

  double near_zero()
  {
    double s = 1e-8;
    return ((std::fabs(e[0]) < s)
         && (std::fabs(e[1]) < s)
         && (std::fabs(e[2]) < s));
  }

  static Vec3 random()
  {
    return Vec3(random_double(), random_double(), random_double());
  }

  static Vec3 random(double min, double max)
  {
    return Vec3(
      random_double(min, max),
      random_double(min, max),
      random_double(min, max)
    );
  }
};

using Point3 = Vec3;

inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
  return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
  return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
  return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(double t, const Vec3& v)
{
  return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vec3 operator*(const Vec3& v, double t)
{
  return t * v;
}

inline Vec3 operator/(const Vec3& v, double t)
{
  return (1/t) * v;
}

inline double dot(const Vec3& u, const Vec3& v)
{
  return u.e[0] * v.e[0]
    + u.e[1] * v.e[1]
    + u.e[2] * v.e[2];
}

inline Vec3 cross(const Vec3& u, const Vec3& v)
{
  return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vec3 unit_vector(const Vec3& v)
{
  return v / v.length();
}

inline Vec3 random_unit_vector()
{
  while (true)
  {
    Vec3 p = Vec3::random(1, -1);
    double len_sq = p.length_squared();
    if ((1e-160 < len_sq) && (len_sq <= 1)) return p / sqrt(len_sq);
  }
}

inline Vec3 random_on_hemisphere(const Vec3& normal)
{
  Vec3 on_unit_sphere = random_unit_vector();
  if (dot(on_unit_sphere, normal) > 0.0)
  {
    return on_unit_sphere;
  }
  else
  {
    return - on_unit_sphere;
  }
}

inline Vec3 reflect(const Vec3& v, const Vec3& n)
{
  return v - 2 * dot(v, n) * n;
}

inline Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat)
{
  double cos_theta = fmin(dot(-uv, n), 1.0);
  Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
  Vec3 r_out_parallel = - std::sqrt(
    std::fabs(1.0 - r_out_perp.length_squared())) * n;
  return r_out_perp + r_out_parallel;
}

auto format_as(Vec3 v);

inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

