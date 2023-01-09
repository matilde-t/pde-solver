#ifndef MATRIXUTILS_H
#define MATRIXUTILS_H

#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<double>> create_matrix(int dim1, int dim2);

std::vector<std::vector<double>>
populate_matrix(std::vector<std::vector<double>> &m, int m_type,
                char switch_options);

template <typename T> void print_vector(const std::vector<T> &v);

template <typename T> void print_matrix(std::vector<std::vector<T>> &m) {
  for (const auto &v : m) {
    print_vector(v);
  }
  std::cout << "\n";
}


class matrix {
private:
    std::vector<std::vector<double>> _m;
public:
    matrix(int dim1, int dim2);
    void populate(int m_type, char switch_options);
    void print();
    void plot(std::string savename);
    void save_csv(std::string savename);

};

#endif // MATRIXUTILS_H
