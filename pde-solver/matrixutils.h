#ifndef MATRIXUTILS_H
#define MATRIXUTILS_H

#include <algorithm>
#include <iostream>
#include <vector>

template <typename T> void print_vector(const std::vector<T> &v);

class matrix {
private:
    std::vector<std::vector<double>> _m;
public:
    matrix(int dim1, int dim2);
    void populate(int m_type, char switch_options);
    void print();
    void plot(std::string savename = "");
    void save_csv(std::string savename);

    friend matrix solve_pde(matrix &f, const matrix &h, int steps, bool show_steps, bool show_final);

};

#endif // MATRIXUTILS_H
