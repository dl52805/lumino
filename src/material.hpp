#pragma once

#include "hittable.hpp"

#include "color.hpp"

struct Material
{
  virtual ~Material() = default;

  virtual bool scatter(
    const Ray& r_in,
    const Hit_Record& rec,
    Color &attenuation,
    Ray &scatter
  ) const
  {
    return false;
  }
};

struct Lambertian : public Material
{
  Color albedo;

  Lambertian(const Color& albedo) : albedo(albedo) {}

  bool scatter(
    const Ray& ray_in,
    const Hit_Record& rec,
    Color &attenuation,
    Ray &scattered
  ) const override
  {
    Vec3 scatter_direction = rec.normal + random_unit_vector();

    if (scatter_direction.near_zero())
    {
      scatter_direction = rec.normal;
    }

    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
  }
};

struct Metal : public Material
{
  Color albedo;
  double fuzz;

  Metal(const Color& albedo, double fuzz)
    : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

  bool scatter(
    const Ray& ray_in,
    const Hit_Record& rec,
    Color &attenuation,
    Ray &scattered
  ) const override
  {
    Vec3 reflected = reflect(ray_in.direction(), rec.normal);
    reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
    scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    return (dot(scattered.direction(), unit_vector(rec.normal)) > 0);
  }
};

struct Diamond : public Material
{
  double refraction_index;
  Color albedo;
  double fuzz;

  Diamond(double refraction_index, Color albedo, double fuzz)
    : refraction_index(refraction_index), albedo(albedo), fuzz(fuzz) {}

  bool scatter(
    const Ray& ray_in,
    const Hit_Record& rec,
    Color &attenuation,
    Ray &scattered
  ) const override
  {
    attenuation = Color(1.0, 1.0, 1.0);
    double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;

    Vec3 unit_direction = unit_vector(ray_in.direction());
    double cos_theta = fmin(dot(- unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = ri * sin_theta > 1.0;
    Vec3 direction;

    if (cannot_refract)
    {
      Vec3 reflected = reflect(ray_in.direction(), rec.normal);
      reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
      scattered = Ray(rec.p, reflected);
      attenuation = albedo;
      return (dot(scattered.direction(), unit_vector(rec.normal)) > 0);
    }
    else direction = refract(unit_direction, rec.normal, ri);

    scattered = Ray(rec.p, direction);
    return true;
  }
};


