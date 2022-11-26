#ifndef IOUTILS_H
#define IOUTILS_H

#include <fstream>
#include <string>
#include <vector>

template <typename T>
void save_csv(const std::vector<std::vector<T>> &v,
              std::string savename) { // save matrix as csv
  std::ofstream file;
  file.open(savename);
  for (const auto &row : v) {
    for (const auto &elem : row) {
      file << elem << ",";
    }
    file << "\n";
  }
  file.close();
}

bool get_input(void);

#endif // IOUTILS_H