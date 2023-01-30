#include "ioutils.h"
#include "matrixutils.h"
#include <iostream>

int main() {

  auto dim_input = get_dim();
  matrix f = matrix(dim_input[0], dim_input[1]);
  matrix h = matrix(dim_input[0], dim_input[1]);

  f.populate(get_f(), 'f');

  h.populate(get_h(), 'h');

  std::cout << "Your matrices are\n f:\n";
  f.print();
  std::cout << "h:\n";
  h.print();

  auto solver_type = get_solver();

  auto num_it = get_iterations();

  show_steps_prompt(f, h, num_it);

  save_csv_prompt(f);

  save_plot_prompt(f);

  return 0;
}
