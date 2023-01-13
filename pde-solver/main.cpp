#include "ioutils.h"
#include "matrixutils.h"
#include "pdesolver.h"
#include <iostream>
#include <matplot/matplot.h>
#include <string>

int main() {
  int dim1_input, dim2_input, f_type, h_type, solver_type;
  std::cout
      << "Let's build a 2D matrix (NxM) for the heat distribution\n"
         "It must be at least a 3x3 matrix\n"
         "First, please input the desired row dimension (N) of your 2D matrix "
         ": ";
  std::cin >> dim1_input;
  if (dim1_input < 3) {
    throw(std::invalid_argument("Invalid dimension"));
  }
  std::cout << "Now, please input the desired column dimension (M) of your 2D "
               "matrix : ";
  std::cin >> dim2_input;
  if (dim2_input < 3) {
    throw(std::invalid_argument("Invalid dimension"));
  }
  matrix f = matrix(dim1_input, dim2_input);
  matrix h = matrix(dim1_input, dim2_input);

  std::cout
      << "Please choose your desired f from the following list:\n 1. Plate with no "
         "heat\n 2. Plate with left heated border\n\n";
  std::cin >> f_type;
  
  f.populate(f_type, 'f');

  std::cout << "Please choose your desired h (internal heat/sink source "
               "distribution) from the following list:\n 1. No internal heat "
               "sources\n "
               "2. One heat source in the middle\n 3. Two heat sources, "
               "equispaced\n 4. One heat source and one sink, equispaced\n\n";
  std::cin >> h_type;
  h.populate(h_type, 'h');

  std::cout << "Your matrices are\n f:\n";
  f.print();
  std::cout << "h:\n";
  h.print();

  std::cin.clear();
  std::cin.ignore();

  std::cout
      << "Please choose your desired relaxation method from the following list:\n 1. Diffusion (visual approximation) \n 2. Jacobi \n 3. Gauss-Seidel\n\n";
  std::cin >> solver_type;

  int num_it;
  std::cout << "The default number of iterations is 50, do you want to change it? Y/n\n";
  auto ask = ask_user();
  if (ask_user()) {
      std::cout << "How many iterations do you want?\n";
      std::string line;
      getline(std::cin, line);
      num_it = stoi(line);
  } else {
      num_it = 50;
  }

  std::cout << "Do you want to see each iteration step? Y/n\n";
  if (ask_user()) {
    solve_pde(f, h, num_it, true, solver_type);
  } else {
    std::cout << "Do you want to see the final step? Y/n\n";
    if (ask_user()) {
      solve_pde(f, h, num_it, false, true, solver_type);
    } else {
      solve_pde(f, h, num_it, false, false, solver_type);
    }
  }

  std::cout << "Do you want to save the final matrix? Y/n\n";
  if (ask_user()) {
    std::cout
        << "Please input the name of the file you want to save the matrix "
           "into (without extension):\n";
    std::string name;
    getline(std::cin, name);
    name.append(".csv");
    f.save_csv(name);
  }

  std::cout << "Do you want to save the final plot? Y/n\n";
  auto save_flag = ask_user();
  std::string name;
  if (save_flag) {
    std::cout << "Please input the name of the file you want to save the plot "
                 "into (without extension):\n";
    getline(std::cin, name);
    name.append(".png");
  }

  f.plot();
  if (save_flag) {
    matplot::save(name);
  }

  return 0;
}
