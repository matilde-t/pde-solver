#include "matrixutils.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <matplot/matplot.h>

std::vector<std::vector<double>> create_matrix(int dim1, int dim2) {
  std::vector<std::vector<double>> m(dim1, std::vector<double>(dim2, 0));
  return m;
}

template <typename T> void print_vector(const std::vector<T> &v) {
  for (const auto &elem : v) {
    std::cout << elem << " ";
  }
  std::cout << "\n";
}

std::vector<std::vector<double>>
populate_matrix(std::vector<std::vector<double>> &m, int m_type,
                char switch_options) {
  if (switch_options == 'f') {
    switch (m_type) {
    case 1:
      break;
    case 2:
      for (auto &v : m) {
        v[0] = 1;
      }
      break;
    default:
      throw(std::invalid_argument("Invalid option"));
    }
  } else {
    switch (m_type) {
      int i, j;
    case 1:
      break; // 1. No internal heat sources
    case 2:  // 2. One heat source in the middle
      i = round(m[0].size() / 2);
      j = round(m.size() / 2);
      m[j][i] = 1;
      break;
    case 3: // 3. Two heat sources, equispaced
      i = round(m[0].size() / 3);
      j = round(m.size() / 2);
      m[j][i] = 1;
      i = round(2 * m[0].size() / 3);
      m[j][i] = 1;
      break;

    case 4: // 4. One heat source and one sink, equispaced
      i = round(m[0].size() / 3);
      j = round(m.size() / 2);
      m[j][i] = 1;
      i = round(2 * m[0].size() / 3);
      m[j][i] = -1;
      break;
    default:
      throw(std::invalid_argument("Invalid option"));
    }
  }
  return m;
}

// Matrix methods

// Matrix constructor
matrix::matrix(int dim1, int dim2){
    std::vector<std::vector<double>> _m(dim1, std::vector<double>(dim2, 0));
};

void matrix::populate(int m_type, char switch_options){
    if (switch_options == 'f') {
        switch (m_type) {
        case 1:
          break;
        case 2:
          for (auto &v : _m) {
            v[0] = 1;
          }
          break;
        default:
          throw(std::invalid_argument("Invalid option"));
        }
      } else {
        switch (m_type) {
          int i, j;
        case 1:
          break; // 1. No internal heat sources
        case 2:  // 2. One heat source in the middle
          i = round(_m[0].size() / 2);
          j = round(_m.size() / 2);
          _m[j][i] = 1;
          break;
        case 3: // 3. Two heat sources, equispaced
          i = round(_m[0].size() / 3);
          j = round(_m.size() / 2);
          _m[j][i] = 1;
          i = round(2 * _m[0].size() / 3);
          _m[j][i] = 1;
          break;

        case 4: // 4. One heat source and one sink, equispaced
          i = round(_m[0].size() / 3);
          j = round(_m.size() / 2);
          _m[j][i] = 1;
          i = round(2 * _m[0].size() / 3);
          _m[j][i] = -1;
          break;
        default:
          throw(std::invalid_argument("Invalid option"));
        }
      }};

void matrix::print(){
    for (const auto &v : _m) {
      print_vector(v);
    }
    std::cout << "\n";
};

void matrix::plot(std::string savename = ""){
    auto fig = matplot::imagesc(_m);
    matplot::colorbar();
    if (savename != "") {
      matplot::save(savename);
    }
    matplot::show();
};

void matrix::save_csv(std::string savename){
    // save matrix as csv
      std::ofstream file;
      file.open(savename);
      for (const auto &row : _m) {
        for (const auto &elem : row) {
          file << elem << ",";
        }
        file << "\n";
      }
      file.close();
};
