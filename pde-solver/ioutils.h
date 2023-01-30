#ifndef IOUTILS_H
#define IOUTILS_H

#include "matrixutils.h"
#include "pdesolver.h"
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

void show_steps_prompt(matrix& f, matrix& h, int &num_it);

void save_csv_prompt(matrix& f);

void save_plot_prompt(matrix& f);

#endif // IOUTILS_H