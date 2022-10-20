#include <string>

#include "shapes.hpp"

shape_type shape_type_from_str(std::string str) {
  to_lower(str);
  
  if      (str == "rectangle") return shape_type::Rectangle;
  else if (str == "ellipse")   return shape_type::Ellipse;
  /**
   * add support for extra shape types here ...
   */
  else                          return shape_type::Unsupported;
}
