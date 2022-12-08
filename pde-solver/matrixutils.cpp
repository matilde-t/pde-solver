#include "matrixutils.h"
#include <cmath>
#include <iostream>

std::vector<std::vector<double>> create_matrix(int dim1, int dim2) {
  std::vector<std::vector<double>> m(dim1, std::vector<double>(dim2, 0));
  return m;
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

std::vector<std::vector<double>> mat_subtract(std::vector<std::vector<double>> a, std::vector<std::vector<double>> b){
    if (a.size()!=a.size()){throw std::invalid_argument( "Vector dimension mismatch: mismatched rows" );}
    if (a[0].size()!=b[0].size()){throw std::invalid_argument( "Vector dimension mismatch: mismatched columns" );}
    std::vector<std::vector<double>> result(a[0].size());
    for(int i = 0; i< a.size(); i++){
        std::transform(a[i].begin(), a[i].end(), b[i].begin(), a[i].begin(), std::minus<double>());
        result[i] = a[i];
    }
    return result;
}
