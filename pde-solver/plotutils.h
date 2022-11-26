#ifndef PLOTUTILS_H
#define PLOTUTILS_H

#include <matplot/matplot.h>
#include <string>
#include <vector>

using namespace matplot;

template <typename T>
void plot(const std::vector<std::vector<T>> &v, std::string savename = "") {
  auto fig = imagesc(v);
  colorbar();
  if (savename != "") {
    save(savename);
  }
  show();
}

#endif // PLOTUTILS_H