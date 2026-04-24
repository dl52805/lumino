#include "color.hpp"

#include <iostream>

void write_color(std::ostream& out, const Color& pixel_color)
{
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  int rbyte = int(255.999 * r);
  int gbyte = int(255.999 * g);
  int bbyte = int(255.999 * b);

  fmt::print(out, "{} {} {}\n", rbyte, gbyte, bbyte);
}

