#pragma once
#include "scalar_field.h"
#include "lens.h"
#include "point2d.h"

class ior_field : public scalarField<double>{
private:
    double x_min, x_max, y_min, y_max;
public:
    // default constructor
    ior_field() = default;
    // constructor
    ior_field(int N_row, int N_col, double x_min, double x_max, double y_min, double y_max, lens l){
        dx = (x_max - x_min) / (N_col - 1);
        dy = (y_max - y_min) / (N_row - 1);
        matrix<double> tmp(N_row, N_col);
        for(auto i = 0; i < N_row; ++i){
            auto x = x_min + i * dx;
            for(auto j = 0; j < N_col; ++j){
                auto y = y_min + j * dy;
                tmp.set_data(i, j, lens_function(x, y, l));
            }
        }
        this->x_min = x_min;
        this->x_max = x_max;
        this->y_min = y_min;
        this->y_max = y_max;
        this->N_col = N_col;
        this->N_row = N_row;
        this->dx = dx;
        this->dy = dy;
        this->data = tmp;
}
    // getter
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
    auto get_N_row(){
        return N_row;
    }
    auto get_N_col(){
        return N_col;
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
};

