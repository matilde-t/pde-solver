#ifndef IOUTILS_H
#define IOUTILS_H

#include "matrixutils.h"
#include <array>
#include <filesystem>
#include <iostream>
#include <matplot/matplot.h>

bool ask_user(void);

std::array<int, 2> get_dim(void);

int get_f(void);

int get_h(void);

int get_solver(void);

int get_iterations(void);

std::array<bool, 2> get_steps(void);

void save_csv_prompt(matrix &f);

void save_plot_prompt(matrix &f);

#endif // IOUTILS_H