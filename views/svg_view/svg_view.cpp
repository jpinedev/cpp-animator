#include <iostream>
#include <map>
#include <string>

#include "../../model/animation.hpp"
#include "../../model/shapes.hpp"
#include "svg_util.hpp"
#include "svg_view.hpp"

using namespace views;

std::string shape_tag_name(shape_type type) {
  switch (type) {
    case shape_type::Rectangle:
      return "rect";
    case shape_type::Ellipse:
      return "ellipse";
    case shape_type::Unsupported:
    default: 
      return "unsupported-shape";
  }
}
std::string pos_attribute_name(shape_type type, std::string axis) {
  return (type == shape_type::Ellipse ? 'c' + axis : axis);
}

std::string width_attribute_name(shape_type type) {
  return (type == shape_type::Ellipse ? "rx" : "width");
}
std::string height_attribute_name(shape_type type) {
  return (type == shape_type::Ellipse ? "ry" : "height");
}
int wh_attribute_value(shape_type type, int wh) {
  return (type == shape_type::Ellipse ? wh / 2 : wh);
}

std::string shape_begin(shape_type type, Frame frame, bool visible) {
  return svg::open_tag(
    shape_tag_name(type),
    {
      svg::attribute(pos_attribute_name(type, "x"), frame.x),
      svg::attribute(pos_attribute_name(type, "y"), frame.y),
      svg::attribute(
        width_attribute_name(type),
        wh_attribute_value(type, frame.width)
      ),
      svg::attribute(
        height_attribute_name(type),
        wh_attribute_value(type, frame.height)
      ),
      svg::attribute_fill(frame.r, frame.g, frame.b),
      svg::attribute_visibility(visible)
    }
  );
}
std::string shape_end(shape_type type) {
  return svg::close_tag(shape_tag_name(type));
}

void views::svg_view::play(Animation* anim) const {
  this->out << svg::open_tag(
    "svg",
    {
      svg::attribute("xmlns", "http://www.w3.org/2000/svg"),
      svg::attribute("width", anim->width),
      svg::attribute("height", anim->height),
      svg::attribute("version", "1.1")
    }
  );

  for(std::map<std::string, AnimatedShape>::const_iterator it = anim->animatedShapes.begin(); it != anim->animatedShapes.end(); ++it) {
    const AnimatedShape& animatedShape = it->second;

    auto last_keyframe = animatedShape.keyframes.begin();
    if (last_keyframe == animatedShape.keyframes.end()) continue;
    
    this->out << shape_begin(animatedShape.type, last_keyframe->frame, last_keyframe->tick == 0);

    this->out << svg::set_visibility(last_keyframe->tick * this->tickrate, true);

    for (auto curr_keyframe = std::next(last_keyframe); curr_keyframe != animatedShape.keyframes.end(); ++curr_keyframe) {
      const Keyframe& last = *last_keyframe;
      const Keyframe& curr = *curr_keyframe;

      const int beginTime = last.tick * this->tickrate;
      const int duration = (curr.tick - last.tick) * this->tickrate;

      if (curr.frame.x != last.frame.x) 
        this->out << svg::animate(
          pos_attribute_name(animatedShape.type, "x"),
          beginTime,
          duration,
          last.frame.x,
          curr.frame.x
        );
        
      if (curr.frame.y != last.frame.y) 
        this->out << svg::animate(
          pos_attribute_name(animatedShape.type, "y"),
          beginTime,
          duration,
          last.frame.y,
          curr.frame.y
        );
        
      if (curr.frame.width != last.frame.width)
        this->out << svg::animate(
          width_attribute_name(animatedShape.type),
          beginTime,
          duration,
          wh_attribute_value(animatedShape.type, last.frame.width),
          wh_attribute_value(animatedShape.type, curr.frame.width)
        );
      
      if (curr.frame.height != last.frame.height)
        this->out << svg::animate(
          height_attribute_name(animatedShape.type),
          beginTime,
          duration,
          wh_attribute_value(animatedShape.type, last.frame.height),
          wh_attribute_value(animatedShape.type, curr.frame.height)
        );
      
      if (curr.frame.r != last.frame.r || curr.frame.g != last.frame.g || curr.frame.b != last.frame.b)
        this->out << svg::animate_fill(
          beginTime,
          duration,
          last.frame.r,
          last.frame.g,
          last.frame.b,
          curr.frame.r,
          curr.frame.g,
          curr.frame.b
        );

      last_keyframe = curr_keyframe;
    }

    this->out << shape_end(animatedShape.type);
  }

  this->out << svg::close_tag("svg");
}
