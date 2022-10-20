#include <map>
#include <set>
#include <string>
#include <sstream>

#include "../model/animation.hpp"
#include "../model/frames.hpp"
#include "../model/shapes.hpp"

#include "animation_builder.hpp"
#include "errors.hpp"

using namespace animation_builder;

const std::string CANVAS_USAGE   = "canvas WIDTH HEIGHT";
const std::string SHAPE_USAGE    = "shape NAME TYPE";
const std::string KEYFRAME_USAGE = "keyframe SHAPE_NAME TICK X_POS Y_POS WIDTH HEIGHT RED GREEN BLUE";
/**
 * add proper usage for extra commands ...
 */

std::string make_usage_error_canvas(std::string err_msg, std::string line)
  { return make_usage_error(err_msg, line, CANVAS_USAGE); }

std::string make_usage_error_shape(std::string err_msg, std::string line)
  { return make_usage_error(err_msg, line, SHAPE_USAGE); }

std::string make_usage_error_keyframe(std::string err_msg, std::string line)
  { return make_usage_error(err_msg, line, KEYFRAME_USAGE); }
/**
 * add usage error for extra commands ...
 */


bool end_of_cmd(std::string *rest_of_line, std::stringstream* stream) {
  if (!std::getline(*stream, *rest_of_line)) {
    *rest_of_line = "";
    return true;
  }
  *stream = std::stringstream(*rest_of_line);

  size_t index = rest_of_line->find_first_not_of(" \t\n\v\f\r");

  if (index == std::string::npos) return true; // has only trailing whitespace characters 
  if (rest_of_line->at(index) == '#') return true; // has a trailing comment

  return false; // has trailing non-whitespace characters
}


Animation* animation_builder::build(std::ifstream* infile, std::string* err_msg) {
  if (!infile->is_open()) {
    *err_msg = make_system_error("file not open");
    return 0;
  }

  Animation* anim = new Animation();

  for (std::string line; std::getline(*infile, line); ) {
    std::string rest_of_line(line);
    std::stringstream stream(rest_of_line);

    if (end_of_cmd(&rest_of_line, &stream)) continue; // line is whitespace or has a comment

    std::string cmd;
    stream >> cmd;

    /**
     *  TODO: Test if char can be extracted (and then interpreted) as an int
     *  if so, check for non-digit character inputs
     */

    if (cmd == "canvas") {
      // canvas WIDTH HEIGHT

      if (anim->width != -1 || anim->height != -1) {
        *err_msg = make_usage_error_canvas("specified more than one canvas", line);
        goto error_out;
      }

      stream >> anim->width >> anim->height;

      if (stream.bad()) {
        *err_msg = make_system_error_readline(line, CANVAS_USAGE);
        goto error_out;
      }

      if (anim->width <= 0 || anim->height <= 0) {
        *err_msg = make_usage_error_canvas("both canvas WIDTH and HEIGHT must be greater than 0", line);
        goto error_out;
      }

      if (!end_of_cmd(&rest_of_line, &stream)) {
        *err_msg = make_usage_error_canvas("too many arguments specified", line);
        goto error_out;
      }

    } else if (cmd == "shape") {
      // shape NAME TYPE

      std::string name, type_str;
      shape_type type(shape_type::Unsupported);

      stream >> name >> type_str;

      if (stream.bad()) {
        *err_msg = make_system_error_readline(line, SHAPE_USAGE);
        goto error_out;
      }

      type = shape_type_from_str(type_str);

      if (name == "") {
        *err_msg = make_usage_error_shape("shape NAME and TYPE must be specified", line);
        goto error_out;
      }

      if (type == shape_type::Unsupported) {
        *err_msg = make_usage_error_shape("unsupported or unrecognized shape type '" + type_str + "'", line);
        goto error_out;
      }

      if (anim->animatedShapes.find(name) != anim->animatedShapes.end()) {
        *err_msg = make_usage_error_shape("already specified a shape of the same NAME '" + name + "'", line);
        goto error_out;
      }

      if (!end_of_cmd(&rest_of_line, &stream)) {
        *err_msg = make_usage_error_shape("too many arguments specified", line);
        goto error_out;
      }

      anim->animatedShapes.insert(
        std::make_pair<std::string, AnimatedShape>(
          std::string(name),
          AnimatedShape(type)
        )
      );

    } else if (cmd == "keyframe") {
      // keyframe SHAPE_NAME TICK X_POS Y_POS WIDTH HEIGHT RED GREEN BLUE

      std::string shape_name;
      Keyframe keyframe;

      stream >> shape_name >> keyframe.tick >> keyframe.frame.x >> keyframe.frame.y >> keyframe.frame.width >> keyframe.frame.height >> keyframe.frame.r >> keyframe.frame.g >> keyframe.frame.b;

      if (stream.bad()) {
        *err_msg = make_system_error_readline(line, KEYFRAME_USAGE);
        goto error_out;
      }

      std::map<std::string, AnimatedShape>::iterator animatedShape = anim->animatedShapes.find(shape_name);

      if (shape_name == "") {
        *err_msg = make_usage_error_keyframe("SHAPE_NAME must be specified", line);
        goto error_out;
      }

      if (animatedShape == anim->animatedShapes.end()) {
        *err_msg = make_usage_error_keyframe("use of undeclared shape '" + shape_name + "'", line);
        goto error_out;
      }

      if (keyframe.tick < 0) {
        *err_msg = make_usage_error_keyframe("TICK must be at least 0", line);
        goto error_out;
      }

      if (keyframe.frame.width < 0 || keyframe.frame.height < 0) {
        *err_msg = make_usage_error_keyframe("WIDTH and HEIGHT must be at least 0", line);
        goto error_out;
      }

      if (keyframe.frame.r < 0 || keyframe.frame.g < 0 || keyframe.frame.b < 0 || keyframe.frame.r > 255 || keyframe.frame.g > 255 || keyframe.frame.b > 255) {
        *err_msg = make_usage_error_keyframe("RED, GREEN, and BLUE must all be between 0 and 255 (inclusive)", line);
        goto error_out;
      }

      if (!end_of_cmd(&rest_of_line, &stream)) {
        *err_msg = make_usage_error_keyframe("too many arguments specified", line);
        goto error_out;
      }

      std::set<Keyframe>& keyframes = animatedShape->second.keyframes;

      if (keyframes.find(keyframe) != keyframes.end()) {
        *err_msg = make_usage_error_keyframe(
          "already specified a keyframe of the same TICK '" + std::to_string(keyframe.tick) + "'",
          line
        );
        goto error_out;
      }

      keyframes.insert(keyframe);

    }
    /**
     * add support for extra commands ...
     */
    else {
      std::string err = "invalid command";
      err += "\n\t"+CANVAS_USAGE;
      err += "\n\t"+SHAPE_USAGE;
      err += "\n\t"+KEYFRAME_USAGE;
      *err_msg = make_system_error(err);
      goto error_out;
    }

    if (infile->bad()) {
      *err_msg = make_system_error("unable to read file");
      goto error_out;
    }
  }

  infile->close();

  if (anim->width <= 0 || anim->height <= 0) {
    *err_msg = make_usage_error_canvas("canvas size must be specified", "make sure you include the following command in your animation file");
    goto error_out;
  }

  *err_msg = "";

  return anim;

  error_out:
    infile->close();
    return 0;
}
