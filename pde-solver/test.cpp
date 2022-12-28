#define CATCH_CONFIG_MAIN
#include "pdesolver.h"
#include <catch2/catch.hpp>
#include <cstdint>
#include "matrixutils.h"

std::vector<std::vector<double>> test_matrix = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {0.0345,0.069,0.1034,0.1379,0.1724,0.2069,0.2414,0.2759,0.3103,0.3448,0.3793,0.4138,0.4483,0.4828,0.5172,0.5517,0.5862,0.6207,0.6552,0.6897,0.7241,0.7586,0.7931,0.8276,0.8621,0.8966,0.931,0.9655,1},
    {0.0345,0.069,0.1034,0.1379,0.1724,0.2069,0.2414,0.2759,0.3103,0.3448,0.3793,0.4138,0.4483,0.4828,0.5172,0.5517,0.5862,0.6207,0.6552,0.6897,0.7241,0.7586,0.7931,0.8276,0.8621,0.8966,0.931,0.9655,1},
    {0.0345,0.069,0.1034,0.1379,0.1724,0.2069,0.2414,0.2759,0.3103,0.3448,0.3793,0.4138,0.4483,0.4828,0.5172,0.5517,0.5862,0.6207,0.6552,0.6897,0.7241,0.7586,0.7931,0.8276,0.8621,0.8966,0.931,0.9655,1},
    {0.0345,0.069,0.1034,0.1379,0.1724,0.2069,0.2414,0.2759,0.3103,0.3448,0.3793,0.4138,0.4483,0.4828,0.5172,0.5517,0.5862,0.6207,0.6552,0.6897,0.7241,0.7586,0.7931,0.8276,0.8621,0.8966,0.931,0.9655,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}
    };

int n = test_matrix.size();
std::vector<double> zero_vect{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
std::vector<double> one_vect{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
std::vector<std::vector<double>> f(n,one_vect);
std::vector<std::vector<double>> h(n,zero_vect);
int steps = 50;
double tol = 1e-06;
std::vector<double> tol_vect(n,tol);
std::vector<std::vector<double>> tol_mat(n,tol_vect);


TEST_CASE("Test and benchmark pde-solver") {
  std::vector<std::vector<double>> a = solve_pde(f, h, steps, false, false);
  REQUIRE(a.size() == test_matrix.size());
  REQUIRE(std::cout << a[1][1] - test_matrix[1][1]);
  //std::cout << test_matrix[a.size()][a[0].size()];

  for(int i=1; i<a.size()-1;++i){
      for(int j=1;j<a[i].size()-1;++j){
             REQUIRE(std::abs(a[i][j]-test_matrix[i][j]) < 1);
     }
  }
}



