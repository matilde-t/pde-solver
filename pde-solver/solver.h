#ifndef PDE_SOLVER_SOLVER_H
#define PDE_SOLVER_SOLVER_H

#include "matrixutils.h"

class solver_manager {
protected:
  matrix &f;
  const matrix &h;
  const int steps = 50;
  const bool show_steps = true;
  const bool show_final = false;

public:
  solver_manager(matrix &f, const matrix &h, int steps = 50,
                 bool show_steps = true, bool show_final = false);
  virtual ~solver_manager(){};
  virtual matrix solve() = 0;
};

class diffusion : public solver_manager {
public:
  diffusion(matrix &f, const matrix &h, int steps = 50, bool show_steps = true,
            bool show_final = false);
  ~diffusion() override{};
  matrix solve() override;
};

class jacobi : public solver_manager {
public:
  jacobi(matrix &f, const matrix &h, int steps = 50, bool show_steps = true,
         bool show_final = false);
  ~jacobi() override{};
  matrix solve() override;
};

class gauss : public solver_manager {
public:
  gauss(matrix &f, const matrix &h, int steps = 50, bool show_steps = true,
        bool show_final = false);
  ~gauss() override{};
  matrix solve() override;
};

#endif // PDE_SOLVER_SOLVER_H
