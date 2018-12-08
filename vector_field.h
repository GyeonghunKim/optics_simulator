#pragma once
#include "scalar_field.h"


template <typename T>
class vectorField{
private:
    // vector field has two scalarField
    scalarField<T> x_field;
    scalarField<T> y_field;
    int N_row, N_col;
    double dx = 1;
    double dy = 1;
public:
    // default constructor
    vectorField() = default;
    // initialize with N_row and N_col
    vectorField(int N_row, int N_col, double dx = 1, double dy = 1){
        scalarField<T> tmp_x(N_row, N_col, dx, dy);
        scalarField<T> tmp_y(N_row, N_col, dx, dy);
        x_field = tmp_x;
        y_field = tmp_y;
        this->N_col = N_col;
        this->N_row = N_row;
        this->dx = dx;
        this->dy = dy;
    }
    // initialize with one value
    vectorField(int N_row, int N_col, T value, double dx = 1, double dy = 1){
        scalarField<T> tmp_x(N_row, N_col, value, dx, dy);
        scalarField<T> tmp_y(N_row, N_col, value, dx, dy);
        x_field = tmp_x;
        y_field = tmp_y;
        this->N_col = N_col;
        this->N_row = N_row;
        this->dx = dx;
        this->dy = dy;
    }
    // initialize with one value
    vectorField(scalarField<T> x_field, scalarField<T> y_field){
        this->x_field = x_field;
        this->y_field = y_field;
        this->N_col = N_col;
        this->N_row = N_row;
        this->dx = dx;
        this->dy = dy;
    }
    // initialize with two functions which initiaize each component of fields
    vectorField(int N_row, int N_col,
                T fx(int, int), T fy(int, int),
                double dx = 1, double dy = 1){
        scalarField<T> tmp_x(N_row, N_col, fx, dx, dy);
        scalarField<T> tmp_y(N_row, N_col, fy, dx, dy);
        x_field = tmp_x;
        y_field = tmp_y;
        this->N_col = N_col;
        this->N_row = N_row;
        this->dx = dx;
        this->dy = dy;
    }
    vectorField(int N_row, int N_col,
                T fx(double, double), double x1_min, double x1_max, double y1_min, double y1_max,
                T fy(double, double), double x2_min, double x2_max, double y2_min, double y2_max,
                double dx =1, double dy = 1){
        scalarField<T> tmp_x(N_row, N_col, fx, x1_min, x1_max, y1_min, y1_max, dx, dy);
        scalarField<T> tmp_y(N_row, N_col, fy, x2_min, x2_max, y2_min, y2_max, dx, dy);
        x_field = tmp_x;
        y_field = tmp_y;
        this->N_col = N_col;
        this->N_row = N_row;
        this->dx = dx;
        this->dy = dy;
    }
    // print function
    void print(){
        std::cout << "( " << std::endl;
        x_field.print();
        std::cout << "," << std::endl;
        y_field.print();
        std::cout << ")" << std::endl;
    }
    // getter
    auto get_x_field(){
        return x_field;
    }
    auto get_y_field(){
        return y_field;
    }
    auto get_N_row(){
        return N_row;
    }
    auto get_N_col(){
        return N_col;
    }
};

template <typename T>
auto get_gradient(scalarField<T> s){
    int N_row = s.get_N_row();
    int N_col = s.get_N_col();
    auto data = s.get_data();
    double dx = s.get_dx();
    double dy = s.get_dy();
    matrix<T> grad_x_data(N_row, N_col);
    for(auto i = 0; i < N_row; ++i){
        for(auto j = 0; j < N_col; ++j){
            if(j == 0){
                grad_x_data.set_data(i, j, (data.get_data(i, j+1) - data.get_data(i, j)) / dx);
            }
            else if(j == N_col - 1){
                grad_x_data.set_data(i, j, (data.get_data(i, j) - data.get_data(i, j-1)) / dx);
            }
            else{
                grad_x_data.set_data(i, j, (data.get_data(i, j+1)  - data.get_data(i, j-1))/(2 * dx));
            }
        }
    }
    scalarField<T> grad_x(grad_x_data);
    matrix<T> grad_y_data(N_row, N_col);
    for(auto i = 0; i < N_row; ++i){
        for(auto j = 0; j < N_col; ++j){
            if(i == 0){
                grad_y_data.set_data(i, j, (data.get_data(i + 1, j) - data.get_data(i, j)) / dy);
            }
            else if(i == N_row - 1){
                grad_y_data.set_data(i, j, (data.get_data(i, j) - data.get_data(i - 1, j)) / dy);
            }
            else{
                grad_y_data.set_data(i, j, (data.get_data(i + 1, j) - data.get_data(i - 1, j))/(2 * dy));
            }
        }
    }
    scalarField<T> grad_y(grad_y_data);
    vectorField<T> tmp(grad_x, grad_y);
    return tmp;
}
