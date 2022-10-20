#ifndef FRAMES_H
#define FRAMES_H

typedef struct frame {
  int x, y;
  int width, height;
  int r, g, b;

  frame(): x(0), y(0), width(0), height(0), r(-1), g(-1), b(-1) { }
} Frame;

typedef struct keyframe {
  int tick;
  Frame frame;

  keyframe(): tick(-1), frame() { }

  friend bool operator<(const keyframe& k1, const keyframe& k2);
  friend int operator-(const keyframe& k1, const keyframe& k2);
} Keyframe;

#endif
