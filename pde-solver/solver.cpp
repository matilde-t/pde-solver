#include "solver.h"

solver_manager::solver_manager(matrix &f, const matrix &h, const int steps,
                               const bool show_steps, const bool show_final)
    : f(f), h(h), steps(steps), show_steps(show_steps),
      show_final(show_final){};

diffusion::diffusion(matrix &f, const matrix &h, const int steps,
                     const bool show_steps, const bool show_final)
    : solver_manager(f, h, steps, show_steps, show_final){};

matrix diffusion::solve() {
  for (int t = 1; t <= steps; ++t) {
    for (int i = 1; i < f._m.size() - 1; ++i) {
      for (int j = 1; j < f._m[i].size() - 1; ++j) {
        f._m[i][j] = (f._m[i - 1][j - 1] + f._m[i - 1][j] + f._m[i][j - 1] +
                      f._m[i][j + 1] + f._m[i + 1][j] + f._m[i + 1][j + 1] +
                      f._m[i - 1][j + 1] + f._m[i + 1][j - 1]) /
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
};

jacobi::jacobi(matrix &f, const matrix &h, const int steps,
               const bool show_steps, const bool show_final)
    : solver_manager(f, h, steps, show_steps, show_final){};

matrix jacobi::solve() {
  double dx = 1;
  double dy = 1;
  double term = 2 * ((dx * dx + dy * dy) / (dx * dx * dy * dy));
  double error = 1e-4;
  double tol = 1e-5;
  matrix f_old = f;

  for (int t = 1; t <= steps && error > tol; ++t) {
    for (int i = 1; i < f._m.size() - 1; ++i) {
      for (int j = 1; j < f._m[i].size() - 1; ++j) {

        f._m[i][j] = ((f_old._m[i + 1][j] + f_old._m[i - 1][j]) / (dx * dx) +
                      (f_old._m[i][j + 1] + f_old._m[i][j - 1]) / (dy * dy) +
                      h._m[i][j]) /
                     term;
      }
    }
    f_old = f;
    if (show_steps) {
      f.print();
      std::cout << "\n";
    }
  }
  if (show_final) {
    f.print();
    h.print();
    std::cout << "\n";
  }

  return f;
};

gauss::gauss(matrix &f, const matrix &h, const int steps, const bool show_steps,
             const bool show_final)
    : solver_manager(f, h, steps, show_steps, show_final){};

matrix gauss::solve() {
  double dx = 1;
  double dy = 1;
  double term = 2 * ((dx * dx + dy * dy) / (dx * dx * dy * dy));
  double error = 1e-4; // 1e-4;
  double tol = 1e-5;   // 1e-5;
  matrix f_old = f;

  for (int t = 1; t <= steps && error > tol; ++t) {
    for (int i = 1; i < f._m.size() - 1; ++i) {
      for (int j = 1; j < f._m[i].size() - 1; ++j) {

        f._m[i][j] =
            ((f._m[i + 1][j] + f._m[i - 1][j]) / pow(dx, 2) +
             (f._m[i][j + 1] + f._m[i][j - 1]) / pow(dy, 2) + h._m[i][j]) /
            term;
      }
    }
    f_old = f;
    if (show_steps) {
      f.print();
    }
  }

  if (show_final) {
    f.print();
    std::cout << "\n";
  }

  return f;
};