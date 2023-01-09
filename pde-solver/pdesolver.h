#ifndef PDESOLVER_H
#define PDESOLVER_H

#include "matrixutils.h"
#include <iostream>
#include <vector>


matrix solve_pde(matrix &f, const matrix &h,
          int steps = 50, bool show_steps = true, bool show_final = false) {
  for (int t = 1; t <= steps; ++t) {
    for (int i = 1; i < f._m.size() - 1; ++i) {
      for (int j = 1; j < f._m[i].size() - 1; ++j) {
        f._m[i][j] = (f._m[i - 1][j - 1] + f._m[i - 1][j] + f._m[i][j - 1] + f._m[i][j + 1] +
                   f._m[i + 1][j] + f._m[i + 1][j + 1] + f._m[i - 1][j + 1] +
                   f._m[i + 1][j - 1]) /
                      8 +
                  h._m[i][j] / 2;
      }
    }
    if (show_steps) {
      f.print();
      std::cout << "\n";
    }
  }
  if (show_final) {
    f.print();
    std::cout << "\n";
  }
  return f;
}

#endif // PDESOLVER_H
