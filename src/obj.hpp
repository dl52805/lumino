#pragma once

#include <vector>
#include "tiny_obj_loader.h"

struct Obj
{
  std::vector<tinyobj::shape_t> shapes;
};

