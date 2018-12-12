#pragma once
#include "matrix.h"
#include "point2d.h"
template <typename T>
class scalarField{
protected:
    // scalar field has matrix
    // scalar field also has "scale" such as dx, dy
    // datatype of scalar field is matrix<T>
    matrix<T> data;
    int N_row, N_col;
    double dx = 1;
    double dy = 1;
    double x_min, x_max, y_min, y_max;
public:
    // default constructor
    scalarField() = default;
    // initialize with matrix and scale(whose default value is 1)
    scalarField(matrix<T> m,
                double dx = 1, double dy = 1){
        this->N_col = m.get_N_col();
        this->N_row = m.get_N_row();
        this->dx = dx;
        this->dy = dy;
        data = m;
    }
    // initialize with just size and scale(whose default value is 1)
    scalarField(int N_row, int N_col,
                double dx = 1, double dy = 1){
        this->N_col = N_col;
        this->N_row = N_row;
        this->dx = dx;
        this->dy = dy;
        data.set_N_col(N_col);
        data.set_N_row(N_row);
        matrix<T> tmp(N_row, N_col);
        data = tmp;

    }
    // initialize with size and one value
    scalarField(int N_row, int N_col, T value,
                double dx = 1, double dy = 1){
        this->N_col = N_col;
        this->N_row = N_row;
        this->dx = dx;
        this->dy = dy;
        matrix<T> tmp(N_row, N_col, value);
        data = tmp;
    }

    // initilize with size and initialize function(whose input variable is integer(I mean it's index not coordinate))
    scalarField(int N_row, int N_col,
                T f(int, int),
                double dx = 1, double dy = 1){
        this->N_col = N_col;
        this->N_row = N_row;
        this->dx = dx;
        this->dy = dy;
        std::vector<std::vector<T>> tmp(N_row, std::vector<T> (N_col, 0));
        for(auto i = 0; i < N_row; ++i){
            for(auto j = 0; j < N_col; ++j){
                tmp[i][j] = f(j, i);
            }
        }
        matrix<T> mat_tmp(tmp);
        data = mat_tmp;
    }

    // initilize with size and initialize function(whose input variable is double(I mean it's coordinate not index))
    // In this function use maximum and minimum value of x and y not dx and dy
    scalarField(int N_row, int N_col,
                T f(double, double),
                double x_min, double x_max, double y_min, double y_max){
        this->N_col = N_col;
        this->N_row = N_row;
        this->x_min = x_min;
        this->y_min = y_min;
        this->x_max = x_max;
        this->y_max = y_max;
        dx = (x_max - x_min) / (N_col - 1);
        dy = (y_max - y_min) / (N_row - 1);
        std::vector<std::vector<T>> tmp(N_row, std::vector<T> (N_col, 0));
        for(auto i = 0; i < N_row; ++i){
            auto x = x_min + i * dx;
            for(auto j = 0; j < N_col; ++j){
                auto y = y_min + j * dy;
                tmp[i][j] = f(y, x);
            }
        }
        matrix<T> mat_tmp(tmp);
        this->data = mat_tmp;
    }

    // initilize with size and initialize function(whose input variable is double(I mean it's coordinate not index))
    scalarField(int N_row, int N_col, double x_min, double y_min , T f(double, double), double dx = 1, double dy = 1){
        this->N_col = N_col;
        this->N_row = N_row;
        this->x_min = x_min;
        this->y_min = y_min;
        this->x_max = x_max;
        this->y_max = y_max;
        std::vector<std::vector<T>> tmp(N_row, std::vector<T> (N_col, 0));
        for(auto i = 0; i < N_row; ++i){
            auto x = x_min + i * dx;
            for(auto j = 0; j < N_col; ++j){
                auto y = y_min + j * dy;
                tmp[i][j] = f(y, x);
            }
        }
        matrix<T> mat_tmp(tmp);
        this->data = mat_tmp;
    }

    // operator overloadings
    scalarField<T> operator+(const scalarField<T> m){
        auto tmp = data + m.data;
        scalarField<T> tmpp(tmp, dx, dy);
        return tmpp;
    }

    scalarField<T> operator+(const matrix<T> m){
        auto tmp = data + m;
        scalarField<T> tmpp(tmp, dx, dy);
        return tmpp;
    }

    scalarField<T> operator-(const scalarField<T> m){
        auto tmp = data - m.data;
        scalarField tmpp(tmp, dx, dy);
        return tmpp;
    }

    scalarField<T> operator-(const matrix<T> m){
        auto tmp = data - m;
        scalarField<T> tmpp(tmp, dx, dy);
        return tmpp;
    }

    scalarField<T> operator*(const scalarField<T> m){
        auto tmp = data * m.data;
        scalarField tmpp(tmp, dx, dy);
        return tmpp;
    }

    scalarField<T> operator*(T c){
        auto tmp = data * c;
        scalarField tmpp(tmp, dx, dy);
        return tmpp;
    }

    scalarField<T> operator = (const scalarField<T> &m){
        data = m.data;
        N_row = m.N_row;
        N_col = m.N_col;
        dx = m.dx;
        dy = m.dy;
        x_min = m.x_min;
        y_min = m.y_min;
        x_max = m.x_max;
        y_max = m.y_max;
        return *this;

    }

    // transpose the field
    void transpose(){
        auto tmp = data.transpose();
        data = tmp;
    }

    // getters
    auto get_N_row(){
        return N_row;
    }
    auto get_N_col(){
        return N_col;
    }
    auto get_data(){
        return data;
    }
    auto get_data(int i, int j){
        return data.get_data(i, j);
    }
    auto get_data(point2D<int> p){
        return data.get_data(p.get_x(), p.get_y());
    }
    auto get_dx(){
        return dx;
    }
    auto get_dy(){
        return dy;
    }
    auto get_x_min(){
        return x_min;
    }
    auto get_y_min(){
        return y_min;
    }
    auto get_x_max(){
        return x_max;
    }
    auto get_y_max(){
        return y_max;
    }

    // value 2 index
    auto x2i(T x){
        auto i = std::floor(x - x_min) / dx;
        return i;
    }
    auto y2j(T y){
        auto j = std::floor(y - y_min) / dy;
        return j;
    }
    // print
    void print(){
        std::cout << "Scalar Field with N_rows = " << N_row << " and N_cols = " << N_col << std::endl;
        std::cout << "dx = " << dx << ", " << "dy = " << dy << std::endl;
        std::cout << "data: " <<std::endl;
        data.print_only_value();
        std::cout << std::endl;
    }
    void print_matlab(){
        data.print_matlab();
        std::cout << std::endl;
    }
    void print_only_value(){
        data.print_only_value();
        std::cout << std::endl;
    }
    void box_smoothing(int kernel_rad = 1){
        auto dat = data.get_data();
        for(int i = kernel_rad; i < N_row - kernel_rad; ++i){
            for(int j = kernel_rad; j < N_col - kernel_rad; ++j){
                data.set_data(i, j, (dat[i - 1][j - 1] + dat[i][j - 1] + dat[i + 1][j - 1]
                                    + dat[i - 1][j] + dat[i][j] + dat[i + 1][j]
                                    + dat[i - 1][j + 1] + dat[i][j + 1] + dat[i + 1][j + 1])/9);
            }
        }
    }
};
