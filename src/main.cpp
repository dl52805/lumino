#include <math.h>

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ostream.h>

#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"

double hit_sphere(const Point3& center, double radius, const Ray& r)
{
  // (C - Q), center - ray_origin
  Vec3 oc = center - r.origin();
  double a = dot(r.direction(), r.direction());
  double b = - 2.0 * dot(r.direction(), oc);
  double c = dot(oc, oc) - radius * radius;
  double discriminant = b * b - 4 * a * c;

  if (discriminant < 0)
  {
    return - 1.0;
  }
  else
  {
    return (- b - sqrt(discriminant)) / (2.0 * a);
  }
}

Color ray_color(const Ray& r)
{
  auto t = hit_sphere(Point3(0, 0, -1), 0.5, r);
  if (t > 0.0)
  {
    Vec3 normal = unit_vector(r.at(t) - Vec3(0, 0, - 1));
    return 0.5 * Color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
  }

  Vec3 unit_direction = unit_vector(r.direction());
  double a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main(int argc, char *argv[])
{
  double aspect_ratio = 16.0 / 9.0;
  size_t image_width  = 400;

  size_t image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  // Camera

  double focal_len = 1.0;
  double viewport_height = 2.0;
  double viewport_width = viewport_height
    * (double(image_width) / image_height);
  Point3 camera_center = Point3(0, 0, 0);

  Vec3 viewport_u = Vec3(viewport_width, 0, 0);
  Vec3 viewport_v = Vec3(0, - viewport_height, 0);

  Vec3 pixel_delta_u = viewport_u / image_width;
  Vec3 pixel_delta_v = viewport_v / image_height;

  Vec3 viewport_upper_left = camera_center - Vec3(0, 0, focal_len)
    - viewport_u / 2 - viewport_v / 2;
  Vec3 pixel_origin_loc = viewport_upper_left
    + 0.5 * (pixel_delta_u + pixel_delta_v);

  fmt::print("P3\n{} {}\n255\n", image_width, image_height);

  for (int j = 0; j < image_height; j++)
  {
    fmt::print(stderr, "\rScanlines remaining: {} ", image_height - j);

    for (int i = 0; i < image_width; i++)
    {
      Vec3 pixel_center = pixel_origin_loc + (i * pixel_delta_u)
        + (j * pixel_delta_v);
      Vec3 ray_dir = pixel_center - camera_center;
      Ray ray(camera_center, ray_dir);

      Color pixel_color = ray_color(ray);
      write_color(std::cout, pixel_color);
    }
  }

  fmt::print(stderr, "\rDone                                       \n");
}


