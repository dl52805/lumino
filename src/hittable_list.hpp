#pragma once

#include <memory>
#include <vector>

#include "hittable.hpp"

using std::make_shared;
using std::shared_ptr;

struct Hittable_List : public Hittable
{
  std::vector<shared_ptr<Hittable>> objects;

  Hittable_List() {}
  Hittable_List(shared_ptr<Hittable> object) { add(object); }

  void clear()
  {
    objects.clear();
  }

  void add(shared_ptr<Hittable> object)
  {
    objects.push_back(object);
  }

  bool hit(const Ray& r, Interval ray_t, Hit_Record& rec) const override
  {
    Hit_Record temp_rec;
    bool hit_anything = false;
    double closest_so_far = ray_t.max;

    for (int i = 0; i < objects.size(); i++)
    {
      if (objects[i]->hit(r, Interval(ray_t.min, closest_so_far), temp_rec))
      {
        hit_anything = true;
        closest_so_far = temp_rec.t;
        rec = temp_rec;
      }
    }

    return hit_anything;
  }
};


