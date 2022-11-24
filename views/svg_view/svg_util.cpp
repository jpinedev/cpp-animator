#include <initializer_list>
#include <string>

#include "svg_util.hpp"

using namespace svg;

std::string inline_open_tag(std::string name, std::initializer_list<std::string> attributes) {
  std::string result = '<' + name;

  for (std::string attr : attributes) {
    result += ' ' + attr;
  }

  return result + '>';
}


std::string svg::tag(std::string name, std::initializer_list<std::string> attributes) {
  return inline_open_tag(name, attributes) + close_tag(name);
}
std::string svg::open_tag(std::string name, std::initializer_list<std::string> attributes) {
  return inline_open_tag(name, attributes) + '\n';
}
std::string svg::close_tag(std::string name) {
  return "</" + name + ">\n";
}


std::string rgb(int r, int g, int b) {
  return "rgb(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ")";
}


std::string svg::attribute(std::string name, std::string value) {
  return name + '=' + '"' + value + '"';
}
std::string svg::attribute(std::string name, int value) {
  return attribute(name, std::to_string(value));
}


std::string svg::attribute_fill(int r, int g, int b) {
  return attribute("fill", rgb(r, g, b));
}

std::string svg::attribute_ms(std::string name, int value) {
  return attribute(name, std::to_string(value) + "ms");
}

std::string svg::attribute_visibility(bool visible) {
  return attribute("visibility", (visible ? "visible" : "hidden"));
}


std::string svg::set(std::string attributeName, int msBegin, std::string value) {
  return tag(
    "set",
    {
      attribute("attributeName", attributeName),
      attribute_ms("begin", msBegin),
      attribute("to", value)
    }
  );
}

std::string svg::set(std::string attributeName, int msBegin, int value) {
  return set(attributeName, msBegin, std::to_string(value));
}

std::string svg::set_visibility(int msBegin, bool visible) {
  return tag(
    "set",
    {
      attribute("attributeName", "visibility"),
      attribute_ms("begin", msBegin),
      attribute("to", (visible ? "visible" : "hidden"))
    }
  );
}


std::string svg::animate(std::string attributeName, int msBegin, int msDuration, std::string from, std::string to) {
  return tag(
    "animate",
    {
      attribute("attributeName", attributeName),
      attribute_ms("begin", msBegin),
      attribute_ms("dur", msDuration),
      attribute("from", from),
      attribute("to", to),
      attribute("fill", "freeze")
    }
  );
}

std::string svg::animate(std::string attributeName, int msBegin, int msDuration, int from, int to) {
  return animate(attributeName, msBegin, msDuration, std::to_string(from), std::to_string(to));
}

std::string svg::animate_fill(int msBegin, int msDuration, int fromR, int fromG, int fromB, int toR, int toG, int toB) {
  return animate("fill", msBegin, msDuration, rgb(fromR, fromG, fromB), rgb(toR, toG, toB));
}