#include "ioutils.h"
#include <iostream>

bool ask_user(void) {
  std::string line;
  std::getline(std::cin, line);
  if (line == "y" || line.empty()) {
    return true;
  } else if (line == "n") {
    return false;
  } else {
    throw(std::invalid_argument("Invalid character"));
  }
}