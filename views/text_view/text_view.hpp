#ifndef TEXT_VIEW_H
#define TEXT_VIEW_H

#include <iostream>

#include "../../model/animation.hpp"
#include "../views.hpp"

namespace views {

  typedef struct text_view : View {
    private:
      std::ostream& out;

    public:
      text_view(std::ostream& _out): out(_out) { }

      virtual void play(Animation* anim) const;
  } TextView;

};

#endif
