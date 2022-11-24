#ifndef SVG_UTIL_H
#define SVG_UTIL_H

#include <initializer_list>
#include <string>

namespace svg {

  std::string tag(std::string name, std::initializer_list<std::string> attributes);
  std::string open_tag(std::string name, std::initializer_list<std::string> attributes);
  std::string close_tag(std::string name);

  std::string attribute(std::string name, std::string value);
  std::string attribute(std::string name, int value);
  std::string attribute_fill(int r, int g, int b);
  std::string attribute_ms(std::string name, int value);
  std::string attribute_visibility(bool visible);

  std::string set(std::string attributeName, int msBegin, std::string value);
  std::string set(std::string attributeName, int msBegin, int value);
  std::string set_visibility(int msBegin, bool visible);

  std::string animate(std::string attributeName, int msBegin, int msDuration, std::string from, std::string to);
  std::string animate(std::string attributeName, int msBegin, int msDuration, int from, int to);
  std::string animate_fill(int msBegin, int dur, int fromR, int fromG, int fromB, int toR, int toG, int toB);

};

#endif
