#include "ioutils.h"

bool ask_user(void) {
  std::string line;
  std::getline(std::cin, line);
  if (line == "y" || line == "Y" || line.empty()) {
    return true;
  } else if (line == "n") {
    return false;
  } else {
    std::cout << "Invalid character, assuming n \n";
    return false;
  }
}

std::vector<matrix> read_matrix(int argc, char *argv[]) {
  std::vector<matrix> result;
  if (argc == 3) {
    std::cout << "Detected user-given files, trying to read...\n";
    matrix f = matrix(argv[1]);
    matrix h = matrix(argv[2]);
    result.push_back(f);
    result.push_back(h);
    if (f.size() != h.size() || f[0].size() != h[0].size()) {
      std::cout
          << "Error: incomptabile sizes! Reverting to standard version \n";
      auto dim_input = get_dim();
      matrix f = matrix(dim_input[0], dim_input[1]);
      matrix h = matrix(dim_input[0], dim_input[1]);

      f.populate(get_f(), 'f');

      h.populate(get_h(), 'h');
      result.push_back(f);
      result.push_back(h);
    }
  } else {
    auto dim_input = get_dim();
    matrix f = matrix(dim_input[0], dim_input[1]);
    matrix h = matrix(dim_input[0], dim_input[1]);

    f.populate(get_f(), 'f');

    h.populate(get_h(), 'h');
    result.push_back(f);
    result.push_back(h);
  }
  return result;
}

std::array<int, 2> get_dim(void) {
  std::array<int, 2> dim;
  std::cout
      << "Let's build a 2D matrix (NxM) for the heat distribution\n"
         "It must be at least a 3x3 matrix\n"
         "First, please input the desired row dimension (N) of your 2D matrix "
         ": ";
  std::cin >> dim[0];
  if (dim[0] < 3) {
    std::cout << "Invalid N dimension: default dimension 30\n";
    dim[0] = 30;
  }
  std::cout << "Now, please input the desired column dimension (M) of your 2D "
               "matrix : ";
  std::cin >> dim[1];
  if (dim[1] < 3) {
    std::cout << "Invalid M dimension: default dimension 30\n";
    dim[1] = 30;
  }
  return dim;
}

int get_f(void) {
  int f_type;
  std::cout << "Please choose your desired f from the following list:\n 1. "
               "Plate with no "
               "heat\n 2. Plate with left heated border\n\n";
  std::cin >> f_type;
  std::cin.clear();
  std::cin.ignore();
  if (f_type < 1 || f_type > 2) {
    std::cout << "Invalid f: default 1. Plate with no heat\n";
    f_type = 1;
  }
  return f_type;
}

int get_h(void) {
  int h_type;
  std::cout << "Please choose your desired h (internal heat/sink source "
               "distribution) from the following list:\n 1. No internal heat "
               "sources\n "
               "2. One heat source in the middle\n 3. Two heat sources, "
               "equispaced\n 4. One heat source and one sink, equispaced\n\n";
  std::cin >> h_type;
  std::cin.clear();
  std::cin.ignore();
  if (h_type < 1 || h_type > 4) {
    std::cout << "Invalid h: default 1. No internal heat sources\n";
    h_type = 1;
    std::chrono::milliseconds sleep_time(3000);
    std::this_thread::sleep_for(sleep_time);
  }
  return h_type;
}

Solvers get_solver(void) {
  int solver_type;
  std::cout << "Please choose your desired relaxation method from the "
               "following list:\n 1. Diffusion (visual approximation) \n 2. "
               "Jacobi \n 3. Gauss-Seidel\n\n";
  std::cin >> solver_type;
  std::cin.clear();
  std::cin.ignore();
  Solvers s{solver_type - 1};
  return s;
}

int get_iterations(void) {
  int num_it;
  std::cout
      << "The default number of iterations is 50, do you want to change it? "
         "Y/n\n";

  if (ask_user()) {
    std::cout << "How many iterations do you want?\n";
    std::string line;
    getline(std::cin, line);
    num_it = stoi(line);
  } else {
    num_it = 50;
  }
  return num_it;
}

std::array<bool, 2> get_steps() {
  std::array steps = {false, false};
  std::cout << "Do you want to see each iteration step? Y/n\n";
  if (ask_user()) {
    steps[0] = true;
  } else {
    std::cout << "Do you want to see the final step? Y/n\n";
    if (ask_user()) {
      steps[1] = true;
    }
  }
  return steps;
}

void save_csv_prompt(matrix &f) {
  std::cout << "Do you want to save the final matrix? Y/n\n";
  if (ask_user()) {
    std::cout
        << "Please input the name of the file you want to save the matrix "
           "into (without extension):\n";
    std::string name;
    getline(std::cin, name);
    name.append(".csv");
    f.save_csv(name);
    auto path = std::filesystem::current_path();
    std::cout << "The file is saved in " << path << '\n';
  }
}

void save_plot_prompt(matrix &f) {
  std::cout << "Do you want to save the final plot? Y/n\n";
  auto save_flag = ask_user();
  std::string name;
  if (save_flag) {
    std::cout << "Please input the name of the file you want to save the plot "
                 "into (without extension):\n";
    getline(std::cin, name);
    name.append(".png");
    auto path = std::filesystem::current_path();
    std::cout << "The image is saved in " << path << '\n';
  }

  f.plot();
  if (save_flag) {
    matplot::save(name);
  }
}
