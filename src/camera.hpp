#pragma once

#include "hittable.hpp"

#include <omp.h>

#include "color.hpp"
#include "material.hpp"

struct Camera
{
  double aspect_ratio = 1.0;
  int image_width = 100;
  int image_height;
  Point3 center;
  Point3 pixel_origin_loc;
  Vec3 pixel_delta_u;
  Vec3 pixel_delta_v;
  double vfov = 90;
  Vec3 u, v, w;
  Point3 look_from = Point3(0, 0, 0);
  Point3 look_at = Point3(0, 0, - 1);
  Vec3 v_up = Vec3(0, 1, 0);
  int samples_per_pixel = 10;
  double pixel_samples_scale;
  int max_depth;

  std::vector<std::vector<Color>> buffer;

  void render(const Hittable& world)
  {
    initialize();

    fmt::print("P3\n{} {}\n255\n", image_width, image_height);

    for (int j = 0; j < image_height; j++)
    {
      fmt::print(stderr, "\rScanlines remaining: {} ", image_height - j);

      #pragma omp parallel for schedule(dynamic, 4)
      for (int i = 0; i < image_width; i++)
      {
        Color pixel_color(0, 0, 0);
        for (int sample = 0; sample < samples_per_pixel; sample++)
        {
          Ray r = get_ray(i, j);
          pixel_color += ray_color(r, max_depth, world);
        }
        buffer.at(j).at(i) = pixel_color;
      }
    }

    for (int j = 0; j < image_height; j++)
    {
      for (int i = 0; i < image_width; i++)
      {
        write_color(std::cout, pixel_samples_scale * buffer.at(j).at(i));
      }
    }

    fmt::print(stderr, "\rDone                                       \n");
  }

  void initialize()
  {
    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    pixel_samples_scale = 1.0 / samples_per_pixel;

    center = look_from;

    double focal_length = (look_from - look_at).length();
    double theta = degrees_to_radians(vfov);
    double h = tan(theta / 2);
    double viewport_height = 2.0 * h * focal_length;
    double viewport_width = viewport_height
      * (double(image_width) / image_height);
    
    w = unit_vector(look_from - look_at);
    u = unit_vector(cross(v_up, w));
    v = cross(w, u);
    
    Vec3 viewport_u = viewport_width * u;
    Vec3 viewport_v = viewport_height * - v;

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    Vec3 viewport_upper_left = center - (focal_length * w)
      - viewport_u / 2
      - viewport_v / 2;
    pixel_origin_loc = viewport_upper_left + 0.5
      * (pixel_delta_u + pixel_delta_v);
    
    buffer = std::vector<std::vector<Color>>(
      image_height, std::vector<Color>(image_width));
  }

  Ray get_ray(int i, int j) const
  {
    Vec3 offset = sample_square();
    Vec3 pixel_sample = pixel_origin_loc
      + ((i + offset.x()) * pixel_delta_u)
      + ((j + offset.y()) * pixel_delta_v);

    Vec3 ray_origin = center;
    Vec3 ray_direction = pixel_sample - ray_origin;

    return Ray(ray_origin, ray_direction);
  }

  Vec3 sample_square() const
  {
    return Vec3(random_double() - 0.5, random_double() - 0.5, 0);
  }

  Color ray_color(const Ray& r, int depth, const Hittable& world) const
  {
    if (depth <= 0) return Color(0, 0, 0);

    Hit_Record rec;

    if (world.hit(r, Interval(0.001, infinity), rec))
    {
      Ray scattered;
      Color attenuation;
      if (rec.mat->scatter(r, rec, attenuation, scattered))
      {
        return attenuation * ray_color(scattered, depth - 1, world);
      }
      return Color(0, 0, 0);
    }

    Vec3 unit_direction = unit_vector(r.direction());
    double a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
  }
};

