#include "ioutils.h"
#include <iostream>

bool get_input(void) {
  std::cin.clear();
  std::cin.ignore();
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