#ifndef PDESOLVER_H
#define PDESOLVER_H

#include <iostream>
#include <vector>
#include "matrixutils.h"

template <typename T>
std::vector<std::vector<T>>
solve_pde(std::vector<std::vector<T>> &f, const std::vector<std::vector<T>> &h,
          int steps = 50, bool show_steps = true, bool show_final = false) {
  for (int t = 1; t <= steps; ++t) {
    for (int i = 1; i < f.size() - 1; ++i) {
      for (int j = 1; j < f[i].size() - 1; ++j) {
        f[i][j] = (f[i - 1][j - 1] + f[i - 1][j] + f[i][j - 1] + f[i][j + 1] +
                   f[i + 1][j] + f[i + 1][j + 1] + f[i - 1][j + 1] +
                   f[i + 1][j - 1]) /
                      (T)8 +
                  h[i][j] / 2;
      }
    }
    if (show_steps) {
      print_matrix(f);
      std::cout << "\n";
    }
  }
  if (show_final) {
    print_matrix(f);
    std::cout << "\n";
  }
  return f;
}

#endif // PDESOLVER_H