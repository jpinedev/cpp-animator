#ifndef SHAPES_H
#define SHAPES_H

#include <string>

#include "../util/util.hpp"

enum class shape_type {
  Unsupported,
  Rectangle,
  Ellipse,
  /**
   * add extra shapes here ...
   */
};

shape_type shape_type_from_str(std::string str);

#endif
