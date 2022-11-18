#include <iostream>
#include <vector>

using namespace std;



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

int main()
{

    cout << "Hello World!" << endl;

    vector<vector<double>> f {{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}};
    int steps = 10;
    for(int t = 1; t <= steps; ++t){
        for(int i = 1; i < f.size()-1; ++i){
            for(int j = 1; j < f[i].size()-1; ++j){
                f[i][j] = (f[i-1][j-1] + f[i-1][j] + f[i][j-1] + f[i][j+1] + f[i+1][j]
                        + f[i+1][j+1] + f[i-1][j+1] + f[i+1][j-1])/8  ;
            }
        }
    print_matrix(f);
    cout << "\n";
    }

    return 0;
}
