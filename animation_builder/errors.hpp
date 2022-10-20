#ifndef ERRORS_H
#define ERRORS_H

#include <string>

namespace animation_builder {

  std::string make_error(const std::string& err_type, const std::string& err_msg);

  std::string make_system_error(std::string err_msg);

  std::string make_system_error_readline(std::string line, std::string proper_usage);

  std::string make_usage_error(std::string err_msg, std::string line, std::string proper_usage);

};

#endif
