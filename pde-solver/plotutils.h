#ifndef PLOTUTILS_H
#define PLOTUTILS_H

#include <matplot/matplot.h>
#include <string>
#include <vector>

template <typename T>
void plot(const std::vector<std::vector<T>> &v, std::string savename = "") {
  auto fig = matplot::imagesc(v);
  matplot::colorbar();
  if (savename != "") {
    matplot::save(savename);
  }
  matplot::show();
}

#endif // PLOTUTILS_H