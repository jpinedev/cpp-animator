#ifndef SVG_VIEW_H
#define SVG_VIEW_H

#include <iostream>

#include "../../model/animation.hpp"
#include "../views.hpp"

namespace views {

  typedef struct svg_view : View {
    private:
      std::ostream& out;
      const int tickrate;

    public:
      svg_view(std::ostream& _out, int _tickrate): out(_out), tickrate(_tickrate) { }

      virtual void play(Animation* anim) const;
  } SVGView;

};

#endif
