#define TINYOBJLOADER_IMPLEMENTATION 
#include "tiny_obj_loader.h"

#include <math.h>

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ostream.h>

#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"

#include "hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

#include "commons.hpp"

#include "interval.hpp"

#include "triangle.hpp"

Color ray_color(const Ray& r, const Hittable& world)
{
  Hit_Record rec;
  if (world.hit(r, Interval(0, infinity), rec))
  {
    return 0.5 * (unit_vector(rec.normal) + Color(1, 1, 1));
  }

  Vec3 unit_direction = unit_vector(r.direction());
  double a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main(int argc, char *argv[])
{
  std::string obj_file = "./assets/diamond.obj";
  tinyobj::ObjReaderConfig reader_config;
  reader_config.triangulate = true;

  tinyobj::ObjReader reader;

  if (!reader.ParseFromFile(obj_file, reader_config))
  {
    if (!reader.Error().empty())
    {
      fmt::print(stderr, "TinyObjReader: {}\n", reader.Error());
    }
    exit(1);
  }

  if (!reader.Warning().empty())
  {
    fmt::print(stderr, "TinyObjReader: {}\n", reader.Warning());
  }

  auto& attrib    = reader.GetAttrib();
  auto& shapes    = reader.GetShapes();
  auto& materials = reader.GetMaterials();

  std::vector<Triangle> triangles;
  Hittable_List world;

  constexpr double scale_factor = 0.05;

  std::vector<Point3> temp_parsed_vertices;
  for (size_t s = 0; s < shapes.size(); s++)
  {
    size_t index_offset = 0;
    for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
    {
      size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

      // loop over vertices in the face
      for (size_t v = 0; v < fv; v++)
      {
        // access to vertex
        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
        tinyobj::real_t vx =
          attrib.vertices[3 * size_t(idx.vertex_index) + 0]
            * scale_factor;
        tinyobj::real_t vy =
          attrib.vertices[3 * size_t(idx.vertex_index) + 1]
            * scale_factor - 0.4;
        tinyobj::real_t vz =
          attrib.vertices[3 * size_t(idx.vertex_index) + 2]
            * scale_factor - 1.0;

        temp_parsed_vertices.push_back(Point3(vx, vy, vz));

        // check if `normal_index` is zero or positive
        // negative = no normal data
        if (idx.normal_index >= 0)
        {
          tinyobj::real_t nx =
            attrib.normals[3 * size_t(idx.normal_index) + 0];
          tinyobj::real_t ny =
            attrib.normals[3 * size_t(idx.normal_index) + 1];
          tinyobj::real_t nz =
            attrib.normals[3 * size_t(idx.normal_index) + 2];
        }

        // check if `texcoord_index` is zero or positive
        // negative = no texcoord data
        if (idx.texcoord_index >= 0)
        {
          tinyobj::real_t tx =
            attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
          tinyobj::real_t ty =
            attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
        }
      }
      index_offset += fv;

      shapes[s].mesh.material_ids[f];

      triangles.push_back(
        Triangle(
          temp_parsed_vertices.at(0),
          temp_parsed_vertices.at(1),
          temp_parsed_vertices.at(2)
        )
      );
      temp_parsed_vertices.clear();

      world.add(make_shared<Triangle>(triangles.back()));
    }
  }

  double aspect_ratio = 16.0 / 9.0;
  size_t image_width  = 400;

  size_t image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  // camera

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

      Color pixel_color = ray_color(ray, world);
      write_color(std::cout, pixel_color);
    }
  }

  fmt::print(stderr, "\rDone                                       \n");
}
