#include "ioutils.h"
#include "matrixutils.h"
#include "solver.h"
#include <iostream>
#include <memory>

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

  auto steps = get_steps();

  std::unique_ptr<solver_manager> pde_solver;

  switch (solver_type) {
  case Solvers::Diffusion:
    pde_solver = std::make_unique<diffusion>(f, h, num_it, steps[0], steps[1]);
    break;
  case Solvers::Jacobi: 
    pde_solver = std::make_unique<jacobi>(f, h, num_it, steps[0], steps[1]);
    break;
  case Solvers::Gauss: 
    pde_solver = std::make_unique<gauss>(f, h, num_it, steps[0], steps[1]);
    break;
  default:
    throw(std::invalid_argument("Invalid option"));
  }

  f = pde_solver->solve();

  save_csv_prompt(f);

  save_plot_prompt(f);

  return 0;
}
