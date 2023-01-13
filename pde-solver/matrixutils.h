#ifndef MATRIXUTILS_H
#define MATRIXUTILS_H

#include <algorithm>
#include <iostream>
#include <vector>

template <typename T> void print_vector(const std::vector<T> &v);

double calcAvg(std::vector<double>& v);

class matrix {
private:
  std::vector<std::vector<double>> _m;

public:
  matrix(int dim1, int dim2);
  matrix(std::vector<std::vector<double>> mat);
  void populate(int m_type, char switch_options);
  void print() const;
  void plot(std::string savename = "");
  void save_csv(std::string savename);
  double max();  // returns the maximum value in the matrix
  matrix abs();  // returns matrix with absolute values
  double avg();
  size_t size();
  std::vector<double> operator[](int i);
  matrix operator-(const matrix& other);


  friend matrix solve_pde(matrix &f, const matrix &h, int steps, bool show_steps, bool show_final,int solver_type);
  friend matrix diffusion(matrix &f, const matrix &h, int steps, bool show_steps, bool show_final);
  friend matrix jacobi(matrix &f, const matrix &h, int steps, bool show_steps, bool show_final);
  friend matrix gauss(matrix &f, const matrix &h, int steps, bool show_steps, bool show_final);
};

#endif // MATRIXUTILS_H
