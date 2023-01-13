#include "matrixutils.h"
#include <iostream>
#include <vector>
#include <cmath>

matrix solve_pde(matrix &f, const matrix &h, int steps = 50,
                 bool show_steps = true, bool show_final = false) {
  for (int t = 1; t <= steps; ++t) {
    for (int i = 1; i < f._m.size() - 1; ++i) {
      for (int j = 1; j < f._m[i].size() - 1; ++j) {
        f._m[i][j] = (f._m[i - 1][j - 1] + f._m[i - 1][j] + f._m[i][j - 1] +
                      f._m[i][j + 1] + f._m[i + 1][j] + f._m[i + 1][j + 1] +
                      f._m[i - 1][j + 1] + f._m[i + 1][j - 1]) /
                         8 +
                     h._m[i][j] / 2;
      }
    }
    if (show_steps) {
      f.print();
      std::cout << "\n";
    }
  }
  if (show_final) {
    f.print();
    std::cout << "\n";
  }
  return f;
}



matrix jacobi(matrix &f, const matrix &h, int steps, bool show_steps, bool show_final){
    double dx = 1;
    double dy = 1;
    double term= 2*(((pow(dx,2))+(pow(dy,2)))/((pow(dx,2))*(pow(dy,2))));
    double error=1e-4;
    double tol=1e-5;
    int t =0;
    matrix f_old = f;

    while(error>tol && t<=steps){
        for (int i = 1; i < f._m.size() - 1; ++i) {
            for (int j = 1; j < f._m[i].size() - 1; ++j) {


                f._m[i][j] =( (f_old._m[i+1][j] + f_old._m[i-1][j])/pow(dx,2) + (f_old._m[i][j+1] + f_old._m[i][j-1])/pow(dy,2) + h._m[i][j] )/term ;

                //f._m[i][j] = (  ((f_old._m[i-1][j]+f_old._m[i+1][j])/(pow(dx,2)))   + ((f_old._m[i][j-1]+f_old._m[i][j+1])/(pow(dy,2)))  + h._m[i][j] ) / term;

                //error = (f - f_old).avg();

            }
        }
        f_old = f;
        t = t+1;
        if (show_steps) {
            f.print();
            h.print();

        }}

    if (show_final) {
        f.print();
        h.print();
        std::cout << "\n";
    }

    return f;
};




matrix gauss(matrix &f, const matrix &h, int steps, bool show_steps, bool show_final){
    double dx = 1;
    double dy = 1;
    double term= 2*(((pow(dx,2))+(pow(dy,2)))/((pow(dx,2))*(pow(dy,2))));
    double error=1e-4;
    double tol=1e-5;
    int t =0;

    while(error>tol && t<steps){
        for (int i = 1; i < f._m.size() - 1; ++i) {
            for (int j = 1; j < f._m[i].size() - 1; ++j) {

                f._m[i][j] =( (f._m[i+1][j] + f._m[i-1][j])/pow(dx,2) + (f._m[i][j+1] + f._m[i][j-1])/pow(dy,2) + h._m[i][j] )/term ;
            }
        }
        t = t+1;
        if (show_steps) {
            f.print();

        }}

    if (show_final) {
        f.print();
        h.print();
        std::cout << "\n";
    }

    return f;
};

