#ifndef VIEWS_H
#define VIEWS_H

#include "../model/animation.hpp"

namespace views {

  typedef struct view {
    virtual void play(Animation* anim) const = 0;
  } View;

};

#endif
