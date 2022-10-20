#ifndef ANIMATION_H
#define ANIMATION_H

#include <map>
#include <set>
#include <string>

#include "frames.hpp"
#include "shapes.hpp"

typedef struct animated_shape {
  shape_type type;
  std::set<Keyframe> keyframes;

  animated_shape(shape_type _type): type(_type), keyframes() { }
} AnimatedShape;

typedef struct animation {
  int width, height;
  std::map<std::string, AnimatedShape> animatedShapes;

  animation(): width(-1), height(-1), animatedShapes() { }
} Animation;

#endif
