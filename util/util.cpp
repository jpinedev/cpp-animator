#include <string>

#include "util.hpp"

void to_lower(std::string& str) {
  for (auto cc = str.begin(); cc != str.end(); ++cc)
    *cc = std::tolower(*cc);
}
