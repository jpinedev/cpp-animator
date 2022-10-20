#include <iostream>
#include <map>
#include <string>

#include "../../model/animation.hpp"
#include "../../model/shapes.hpp"
#include "text_view.hpp"

using namespace views;

std::string str_from_shape_type(shape_type type) {
  switch (type) {
    case shape_type::Rectangle:
      return "rectangle";
    case shape_type::Ellipse:
      return "ellipse";
    case shape_type::Unsupported:
    default:
      return "unsupported";
  }
}

void views::text_view::play(Animation* anim) const {
  this->out << "canvas " << anim->width << " " << anim->height << std::endl;

  for(std::map<std::string, AnimatedShape>::const_iterator it = anim->animatedShapes.begin(); it != anim->animatedShapes.end(); ++it) {
    const std::string& name = it->first;
    const AnimatedShape& animatedShape = it->second;
    this->out << "shape " << name << " " << str_from_shape_type(animatedShape.type) << std::endl;

    for (auto keyframe_it = animatedShape.keyframes.begin(); keyframe_it != animatedShape.keyframes.end(); ++keyframe_it) {
      const Keyframe& keyframe = *keyframe_it;
      this->out << "keyframe "
        << name << " "
        << keyframe.tick << " "
        << keyframe.frame.x << " "
        << keyframe.frame.y << " "
        << keyframe.frame.width << " "
        << keyframe.frame.height << " "
        << keyframe.frame.r << " "
        << keyframe.frame.g << " "
        << keyframe.frame.b << std::endl;
    }
  }
}
