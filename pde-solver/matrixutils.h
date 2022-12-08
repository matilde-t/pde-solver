#ifndef MATRIXUTILS_H
#define MATRIXUTILS_H

#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<double>> create_matrix(int dim1, int dim2);

std::vector<std::vector<double>>
populate_matrix(std::vector<std::vector<double>> &m, int m_type,
                char switch_options);

template <typename T> void print_vector(const std::vector<T> &v) {
  for (const auto &elem : v) {
    std::cout << elem << " ";
  }
  std::cout << "\n";
}

template <typename T> void print_matrix(std::vector<std::vector<T>> &m) {
  for (const auto &v : m) {
    print_vector(v);
  }
  std::cout << "\n";
}


std::vector<std::vector<double>> mat_subtract(std::vector<std::vector<double>> a, std::vector<std::vector<double>> b);



#endif // MATRIXUTILS_H
