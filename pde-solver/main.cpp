#include <iostream>
#include <vector>
#include <matplot/matplot.h>

using namespace std;
using namespace matplot;

vector<vector<double>> create_matrix(int dim1, int dim2){
    vector<vector<double>> m (dim1, vector<double> (dim2,0));
    return m;
}

vector<vector<double>> populate_matrix(vector<vector<double>>& m, int m_type, char switch_options){
    if (switch_options == 'f'){
        switch (m_type) {
            case 1: break;
            case 2:
                for(auto& v : m){v[0] = 1;}
                break;
        }
    }
    else{
        switch (m_type) {
            int i,j;
            case 1: break; // 1. No internal heat sources
            case 2:  // 2. One heat source in the middle
                i = round(m[0].size()/2);
                j = round(m.size()/2);
                m[j][i] = 1;
                break;
            case 3:  // 3. Two heat sources, equispaced
                i = round(m[0].size()/3);
                j = round(m.size()/2);
                m[j][i] = 1;
                i = round(2*m[0].size()/3);
                m[j][i] = 1;
                break;

            case 4: // 4. One heat source and one sink, equispaced
                i = round(m[0].size()/3);
                j = round(m.size()/2);
                m[j][i] = 1;
                i = round(2*m[0].size()/3);
                m[j][i] = -1;
                break;
        }
    }
    return m;
}

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
    int dim1_input, dim2_input, f_type, h_type;
    cout << "Let's build a 2D matrix (NxM) for the heat distribution\n"
            "It must be at least a 3x3 matrix\n"
            "First, please input the desired row dimension (N) of your 2D matrix : ";
    cin >> dim1_input;
    cout << "Now, please input the desired column dimension (M) of your 2D matrix : ";
    cin >> dim2_input;
    auto f = create_matrix(dim1_input, dim2_input);
    auto h = f;

    cout << "Please your desired f from the following list:\n 1. Plate with no heat\n 2. Plate with left heated border\n\n";
    cin >> f_type;
    f = populate_matrix(f,f_type,'f');

    cout << "Please choose your desired h (internal heat/sink source distribution) from the following list:\n 1. No internal heat sources\n "
            "2. One heat source in the middle\n 3. Two heat sources, equispaced\n 4. One heat source and one sink, equispaced\n\n";
    cin >> h_type;
    h = populate_matrix(h,h_type,'h');

    cout << "Your matrices are\n h:\n";
    print_matrix(f);
    cout << "h:\n";
    print_matrix(h);


    //vector<vector<double>> f {{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}};

    solve_pde (f, 50, false, true);
    save_csv(f, "f.csv");
    plot(f);

    return 0;
}
