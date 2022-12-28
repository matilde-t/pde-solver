#include "ioutils.h"
#include "matrixutils.h"
#include "pdesolver.h"
#include "plotutils.h"
#include <cmath>
#include <iostream>
#include <matplot/matplot.h>
#include <string>
#include <vector>

using namespace std;
using namespace matplot;

int main() {
  int dim1_input, dim2_input, f_type, h_type;
  cout << "Let's build a 2D matrix (NxM) for the heat distribution\n"
          "It must be at least a 3x3 matrix\n"
          "First, please input the desired row dimension (N) of your 2D matrix "
          ": ";
  cin >> dim1_input;
  if (dim1_input < 3) {
    throw(std::invalid_argument("Invalid dimension"));
  }
  cout << "Now, please input the desired column dimension (M) of your 2D "
          "matrix : ";
  cin >> dim2_input;
  if (dim2_input < 3) {
    throw(std::invalid_argument("Invalid dimension"));
  }
  auto f = create_matrix(dim1_input, dim2_input);
  auto h = f;

  cout << "Please your desired f from the following list:\n 1. Plate with no "
          "heat\n 2. Plate with left heated border\n\n";
  cin >> f_type;
  f = populate_matrix(f, f_type, 'f');

  cout << "Please choose your desired h (internal heat/sink source "
          "distribution) from the following list:\n 1. No internal heat "
          "sources\n "
          "2. One heat source in the middle\n 3. Two heat sources, "
          "equispaced\n 4. One heat source and one sink, equispaced\n\n";
  cin >> h_type;
  h = populate_matrix(h, h_type, 'h');

  cout << "Your matrices are\n f:\n";
  print_matrix(f);
  cout << "h:\n";
  print_matrix(h);

  std::cin.clear();
  std::cin.ignore();

  int num_it;
  cout << "The default number of iterations is 50, do you want to change it? "
          "Y/n\n";

  if (ask_user()) {
    cout << "How many iterations do you want?\n";
    string line;
    getline(cin, line);
    num_it = stoi(line);
  } else {
    num_it = 50;
  }

  cout << "Do you want to see each iteration step? Y/n\n";
  if (ask_user()) {
    solve_pde(f, h, num_it, true);
  } else {
    cout << "Do you want to see the final step? Y/n\n";
    if (ask_user()) {
      solve_pde(f, h, num_it, false, true);
    } else {
      solve_pde(f, h, num_it, false, false);
    }
  }

  cout << "Do you want to save the final matrix? Y/n\n";
  if (ask_user()) {
    cout << "Please input the name of the file you want to save the matrix "
            "into (without extension):\n";
    string name;
    getline(cin, name);
    name.append(".csv");
    save_csv(f, name);
  }

  cout << "Do you want to save the final plot? Y/n\n";
  auto save_flag = ask_user();
  string name;
  if (save_flag) {
    cout << "Please input the name of the file you want to save the plot "
            "into (without extension):\n";
    getline(cin, name);
    name.append(".png");
  }

  plot(f);
  if (save_flag) {
    save(name);
  }

  return 0;
}
