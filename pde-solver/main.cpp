#include <iostream>
#include <vector>
#include <matplot/matplot.h>

using namespace std;
using namespace matplot;

template <typename T>
void plot(const vector<vector<T>>& v, std::string savename = ""){  // plot matrix as an image
            matplot::imagesc(v);
            matplot::colorbar();
            matplot::show();
            if(not(savename == "")){
                matplot::save(savename);
            }
        }


template <typename T>
void print_vector(const std::vector<T>& v){
    for (const auto& elem : v){
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

template <typename T>
void print_matrix(std::vector<std::vector<T>>& m){
    for (const auto& v : m){
        print_vector(v);
    }
}

template <typename T>
void solve_pde (vector<vector<T>> & f, int steps = 10, bool show_steps = true, bool show_final = false) {
    for(int t = 1; t <= steps; ++t){
        for(int i = 1; i < f.size()-1; ++i){
            for(int j = 1; j < f[i].size()-1; ++j){
                f[i][j] = (f[i-1][j-1] + f[i-1][j] + f[i][j-1] + f[i][j+1] + f[i+1][j]
                        + f[i+1][j+1] + f[i-1][j+1] + f[i+1][j-1])/(T)8  ;
            }
        }
    if (show_steps) {
        print_matrix(f);
        cout << "\n";
    }
    }
    if (show_final) {
        print_matrix(f);
        cout << "\n";
    }
}


template <typename T>
void save_csv(const vector<vector<T>>& v, std::string savename = ""){  // save matrix as csv
    std::ofstream file;
    file.open(savename);
    for (const auto& row : v){
        for (const auto& elem : row){
            file << elem << ",";
        }
        file << "\n";
    }
    file.close();
}

int main()
{
    vector<vector<double>> f {{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}};

    solve_pde (f, 50, false, true);
    save_csv(f, "f.csv");

    return 0;
}
