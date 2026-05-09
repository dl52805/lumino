#include <memory>
#define TINYOBJLOADER_IMPLEMENTATION 
#include "tiny_obj_loader.h"

#include <math.h>

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ostream.h>

#include "vec3.hpp"
#include "hittable_list.hpp"

#include "commons.hpp"

#include "triangle.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "material.hpp"

int main(int argc, char *argv[])
{
  std::shared_ptr<Lambertian> material_ground
    = std::make_shared<Lambertian>(
      Color(0.5, 0.5, 0.5));
  std::shared_ptr<Metal> material_diamond
    = std::make_shared<Metal>(Color(0.5194, 0.7804, 0.8157), 0.0);
  std::shared_ptr<Lambertian> material_sphere
    = std::make_shared<Lambertian>(
      Color(0.5294, 0.7804, 0.8157));

  std::string obj_file = "./assets/diamond_cut.obj";
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
          attrib.vertices[3 * size_t(idx.vertex_index) + 0];
        tinyobj::real_t vy =
          attrib.vertices[3 * size_t(idx.vertex_index) + 1];
        tinyobj::real_t vz =
          attrib.vertices[3 * size_t(idx.vertex_index) + 2];

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
          temp_parsed_vertices.at(2),
          material_diamond
        )
      );
      temp_parsed_vertices.clear();

      world.add(make_shared<Triangle>(triangles.back()));
    }
  }

  // world.add(make_shared<Sphere>(Point3(0, 0, - 1), 1.5, material_diamond));
  world.add(make_shared<Sphere>(
    Point3(2, 1.05, 2), 1, material_sphere));
  world.add(make_shared<Sphere>(
    Point3(0, - 100.5, - 1), 100, material_ground));

  // camera

  Camera cam;

  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 1200;
  cam.samples_per_pixel = 50;
  cam.max_depth = 35;

  cam.vfov = 90;
  cam.look_from = Point3(2, 1, - 3);
  cam.look_at = Point3(0, 0, - 0.2);
  cam.v_up = Point3(0, 1, 0);

  cam.render(world);
}

