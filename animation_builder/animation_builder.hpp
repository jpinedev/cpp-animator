#ifndef ANIM_BUILDER_H
#define ANIM_BUILDER_H

#include <fstream>
#include <string>

#include "../model/animation.hpp"

namespace animation_builder {

  /**
   * @param infile a valid .anim file for reading from
   * @param err_msg a log for any problems with the state of the `infile` or the commands
   * 
   * @returns 0 if any errors occured while building the animation, else returns the compiled animation
   */
  Animation* build(std::ifstream* infile, std::string* err_msg);
  
}

#endif
