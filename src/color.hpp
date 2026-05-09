#pragma once

#include "vec3.hpp"

using Color = Vec3;

inline double linear_to_gamma(double linear_component)
{
  if (linear_component > 0) return sqrt(linear_component);
  return 0;
}

void write_color(std::ostream& out, const Color& pixel_color);

