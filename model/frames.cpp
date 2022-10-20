#include "frames.hpp"

bool operator<(const keyframe& k1, const keyframe& k2) {
  return k1.tick < k2.tick;
}

int operator-(const keyframe& k1, const keyframe& k2) {
  return k1.tick - k2.tick;
}
