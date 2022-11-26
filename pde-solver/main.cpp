#include "ioutils.h"
#include "matrixutils.h"
#include "pdesolver.h"
#include "plotutils.h"
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
  cout << "Now, please input the desired column dimension (M) of your 2D "
          "matrix : ";
  cin >> dim2_input;
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

  int num_it;
  cout << "The default number of iterations is 50, do you want to change it? "
          "y/n\n";

  if (get_input()) {
    cout << "How many iterations do you want?\n";
    cin >> num_it;
  } else {
    num_it = 50;
    ;
  }

  char show_it;
  cout << "Do you want to see each iteration step? y/n\n";
  cin >> show_it;

  switch (show_it) {
  case 'y':
    solve_pde(f, h, num_it, true, true);
    break;

  default:
    break;
  }

  save_csv(f, "f.csv");
  plot(f);
  save("test.png");

  return 0;
}
