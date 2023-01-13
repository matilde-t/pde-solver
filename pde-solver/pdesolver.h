#ifndef PDESOLVER_H
#define PDESOLVER_H

#include "matrixutils.h"
#include <iostream>
#include <vector>

matrix solve_pde(matrix &f, const matrix &h, int steps = 50,
                 bool show_steps = true, bool show_final = false);

matrix jacobi(matrix &f, const matrix &h, int steps = 200, bool show_steps = true, bool show_final = false);

matrix gauss(matrix &f, const matrix &h, int steps = 200, bool show_steps = true, bool show_final = false);

#endif // PDESOLVER_H
