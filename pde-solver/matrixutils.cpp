#include "matrixutils.h"

template <typename T> void print_vector(const std::vector<T> &v) {
  for (const auto &elem : v) {
    std::cout << elem << " ";
  }
  std::cout << "\n";
}

double calcAvg(
    std::vector<double> &v) { // computes the average for a vector of doubles
  int const count = static_cast<float>(v.size());
  return std::reduce(v.begin(), v.end()) / count;
}

// Matrix methods

// Matrix constructors
matrix::matrix(int dim1, int dim2) {
  std::vector<std::vector<double>> m(dim1, std::vector<double>(dim2, 0));
  _m = m;
};

matrix::matrix(std::vector<std::vector<double>> mat) { _m = mat; }

// Populate matrix with predefined cases
void matrix::populate(int m_type, char switch_options) {
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
  }
};

void matrix::print() const {
  for (const auto &v : _m) {
    print_vector(v);
  }
  std::cout << "\n";
};

void matrix::plot(std::string savename) {
  auto fig = matplot::imagesc(_m);
  matplot::colorbar();
  if (savename != "") {
    matplot::save(savename);
  }
  matplot::show();
};

void matrix::save_csv(std::string savename) {
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

matrix matrix::abs() { // returns matrix with absolute values
  double max = -400;
  auto m = _m;
  for (auto &v : m) {
    for (auto &n : v) {
      n = std::abs(n);
    }
  }
  return matrix(m);
}

double matrix::max() { // returns the maximum value in the matrix
  double max = -400;
  for (const auto &v : _m) {
    double result = *std::max_element(v.begin(), v.end());
    if (result > max) {
      max = result;
    }
  }
  return max;
}

double matrix::avg() { // computes the average for a 2D matrix expressed as a
                       // vector of vectors with doubles
  double sum = 0;
  for (std::vector<double> &subvect : _m) {
    sum += calcAvg(subvect) / _m.size();
  }
  return sum;
}

size_t matrix::size() { return _m.size(); };

std::vector<double> matrix::operator[](int i) { return _m[i]; }

matrix matrix::operator-(const matrix &other) {
  if (_m.size() != other._m.size()) {
    throw std::invalid_argument("Vector dimension mismatch");
  }
  std::vector<std::vector<double>> v3(_m.size());
  for (int i = 0; i < _m.size(); i++) {
    std::transform(_m[i].begin(), _m[i].end(), other._m[i].begin(),
                   _m[i].begin(), std::minus<double>());
    v3[i] = _m[i];
  }
  return matrix(v3);
}
