#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include "point2d.h"

template <typename T>
class matrix{
protected:
    // data type is vector of vector
    // T can be int or double
    std::vector<std::vector<T>> data;
    int N_row = 0;
    int N_col = 0;

public:
    // default constructor
    matrix() {
        data.push_back(std::vector<T>(1, 0));
        this->N_row = 1;
        this->N_col = 1;
    }
    // initialize with size
    matrix(int N_row, int N_col) {
        std::vector<std::vector<T>> tmp(N_row, std::vector<T> (N_col, 0));
        this->N_col = N_col;
        this->N_row = N_row;
        data = tmp;
    }
    // initialize with size and specific value
    matrix(int N_row, int N_col, T value) {
        std::vector<std::vector<T>> tmp(N_row, std::vector<T> (N_col, value));
        this->N_col = N_col;
        this->N_row = N_row;
        data = tmp;
    }
    //initialization with std::vector<std::vector<T>>
    matrix(std::vector<std::vector<T>> m) {
        this->N_col = m.size();
        this->N_row = m[0].size();
        data = m;
    }
    // print function
    void print(){
        auto siz1 = data.size();
        auto siz2 = data[0].size();
        std::cout << "Matrix with N_rows = " << N_row << " and N_cols = " << N_col << std::endl;
        std::cout << "data: " <<std::endl;
        for(auto i = 0; i < siz1; ++i){
            for(auto j = 0; j < siz2; ++j){
                std::cout << std::setw(5) << data[i][j] << "  ";
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }

    void print_only_value(){
        auto siz1 = data.size();
        auto siz2 = data[0].size();
        for(auto i = 0; i < siz1; ++i){
            for(auto j = 0; j < siz2; ++j){
                std::cout << std::setw(5) << data[i][j] << "  ";
            }
            std::cout << "\n";
        }
    }
    void print_matlab(){
        auto siz1 = data.size();
        auto siz2 = data[0].size();
        std::cout << "[";
        for(auto i = 0; i < siz1; ++i){
            for(auto j = 0; j < siz2; ++j){
                std::cout << data[i][j] << " ";
            }
            std::cout << ";\n";
        }
        std::cout << "]";
    }
    // operator overloadings
    matrix operator+(const matrix m){
        auto N_row_add = N_row < m.N_row ? N_row : m.N_row;
        auto N_col_add = N_col < m.N_col ? N_col : m.N_col;
        matrix<T> tmp(N_row_add, N_col_add);
        for(auto i = 0; i < N_row_add; ++i){
            for(auto j = 0; j < N_col_add; ++j){
                tmp.data[i][j] = data[i][j] + m.data[i][j];
            }
        }
        tmp.N_row = N_row;
        tmp.N_col = N_col;

        return tmp;
    }
    matrix operator-(const matrix m){
        auto N_row_add = N_row < m.N_row ? N_row : m.N_row;
        auto N_col_add = N_col < m.N_col ? N_col : m.N_col;
        matrix<T> tmp(N_row_add, N_col_add);
        for(auto i = 0; i < N_row_add; ++i){
            for(auto j = 0; j < N_col_add; ++j){
                tmp.data[i][j] = data[i][j] - m.data[i][j];
            }
        }
        tmp.N_row = N_row;
        tmp.N_col = N_col;
        return tmp;
    }
    matrix operator*(const matrix m){
        auto tmp_N_row = N_row;
        auto tmp_N_col = m.N_col;
        matrix<T> tmp(tmp_N_row, tmp_N_col);
        if(N_col != m.N_row){
            std::cout << "Dimension Error!" << std::endl;
            return tmp;
        }
        auto tmp_k = N_col;
        for(auto i = 0; i < tmp_N_row; ++i){
            for(auto j = 0; j < tmp_N_col; ++j){
                for(auto k = 0; k < tmp_k; ++k){
                    tmp.data[i][j] += data[i][k] * m.data[k][j];
                }
            }
        }
        tmp.N_row = tmp_N_row;
        tmp.N_col = tmp_N_col;
        return tmp;
    }

    matrix operator*(const T c){
        matrix<T> tmp(data);
        auto tmp_k = N_col;
        for(auto i = 0; i < N_row; ++i){
            for(auto j = 0; j < N_col; ++j){
                    tmp.data[i][j] *= c;
            }
        }
        return tmp;
    }
    matrix operator = (const matrix m){
        data = m.data;
        N_row = m.N_row;
        N_col = m.N_col;
        return *this;
    }

    // transpose the data
    // destructive function
    auto transpose(){
        auto tmp_N_row = N_col;
        auto tmp_N_col = N_row;
        std::vector<std::vector<T>> tmp(tmp_N_row, std::vector<T> (tmp_N_col, 0));
        for(auto i = 0; i < tmp_N_row; ++i){
            for(auto j = 0; j < tmp_N_col; ++j){
                tmp[i][j] = data[j][i];
            }
        }
        N_col = tmp_N_col;
        N_row = tmp_N_row;
        data = tmp;
    }

    // getters and setters
    auto get_data(int i, int j){
        return data[i][j];
    }
    auto get_data(){
        return data;
    }
    auto get_data(point2D<int> p){
        return data[p.get_x()][p.get_y()];
    }
    auto get_N_row(){
        return N_row;
    }
    auto get_N_col(){
        return N_col;
    }
    auto set_data(int i, int j, T value){
        data[i][j] = value;
    }

    // functions about data
    T max() {
        T max_val = data[0][0];
        for (auto i = 0; i < N_row; ++i) {
            for (auto j = 0; j < N_col; ++j) {
                max_val = (data[i][j] < max_val) ? max_val : data[i][j];
            }
        }
        return max_val;
    }

    T min() {
        T min_val = data[0][0];
        for (auto i = 0; i < N_row; ++i) {
            for (auto j = 0; j < N_col; ++j) {
                min_val = (data[i][j] > min_val) ? min_val : data[i][j];
            }
        }
        return min_val;
    }
    auto add_for_IOR_field(matrix<double> m){
        matrix<double> ret(m);
        for (auto i = 0; i < N_row; ++i) {
            for (auto j = 0; j < N_col; ++j) {
                if(data[i][j] != 1){
                    ret.set_data(i, j, data[i][j]);
                }
            }
        }
        return ret;
    }
    friend class lens_body;
};
