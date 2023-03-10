#include "ioutils.h"
#include "matrixutils.h"
#include "solver.h"
#include <iostream>
#include <memory>
#include <thread>

int main(int argc, char *argv[]) {

  auto read = read_matrix(argc, argv);

  auto f = read[0];
  auto h = read[1];

  std::cout << "Your matrices are\n f:\n";
  f.print();
  std::cout << "h:\n";
  h.print();

  auto solver_type = get_solver();

  auto num_it = get_iterations();

  auto steps = get_steps();

  std::unique_ptr<solver_manager> pde_solver;

  try {
    switch (solver_type) {
    case Solvers::Diffusion:
      pde_solver =
          std::make_unique<diffusion>(f, h, num_it, steps[0], steps[1]);
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
  } catch (...) {
    std::chrono::milliseconds sleep_time(3000);
    std::cout << "Invalid solver selected: auto select Gauss-Seidel... \n";
    std::this_thread::sleep_for(sleep_time);
    pde_solver = std::make_unique<gauss>(f, h, num_it, steps[0], steps[1]);
  }

  f = pde_solver->solve();

  save_csv_prompt(f);

  save_plot_prompt(f);

  return 0;
}
