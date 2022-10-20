#include <string>

#include "errors.hpp"

using namespace animation_builder;

std::string animation_builder::make_error(const std::string& err_type, const std::string& err_msg)
  { return err_type + " error: " + err_msg; }

std::string animation_builder::make_system_error(std::string err_msg)
  { return make_error("System", err_msg); }

std::string animation_builder::make_system_error_readline(std::string line, std::string proper_usage)
  { return make_system_error("unable to read line\n\tseen: " + line + "\n\texpected: " + proper_usage); }

std::string animation_builder::make_usage_error(std::string err_msg, std::string line, std::string proper_usage)
  { return make_error("Usage", err_msg + "\n\t" + line + "\n\t" + proper_usage); }