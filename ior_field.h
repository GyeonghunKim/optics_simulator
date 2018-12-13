#pragma once
#include "scalar_field.h"
#include "lens.h"
#include "point2d.h"

class ior_field : public scalarField<double>{
private:
    double x_min, x_max, y_min, y_max;
    matrix<double> data;
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
                tmp.set_data(i, j, lens_function(x, y, l, l.get_lens_type()));
                // std::cout << "**************************" << std::endl;
                // std::cout << lens_function(x, y, l, l.get_lens_type()) << std::endl;
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
    ior_field(const ior_field &m){
        data = m.data;
        N_row = m.N_row;
        N_col = m.N_col;
        dx = m.dx;
        dy = m.dy;
        x_min = m.x_min;
        y_min = m.y_min;
        x_max = m.x_max;
        y_max = m.y_max;
        std::cout << "in ior_field";
        std::cout << x_min << "\t" << x_max << "\t" << y_min << "\t" << y_max <<std::endl;
    }

    ior_field(scalarField m){
        data = m.get_data();
        N_row = m.get_N_row();
        N_col = m.get_N_col();
        dx = m.get_dx();
        dy = m.get_dy();
        x_min = m.get_x_min();
        y_min = m.get_y_min();
        x_max = m.get_x_max();
        y_max = m.get_y_max();
    }

    ior_field(matrix<double> m,
              double dx, double dy,
              double x_min, double x_max, double y_min, double y_max){
        this->data = m;
        this->N_row = m.get_N_row();
        this->N_col = m.get_N_col();
        this->dx = dx;
        this->dy = dy;
        this->x_min = x_min;
        this->y_min = y_min;
        this->x_max = x_max;
        this->y_max = y_max;
    }

    // print functions
    void print(){
        data.print();
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

    double get_value_bilinear(double x, double y){
        std::cout << "this is from get_value_bilinear" << std::endl;
        std::cout << x_min << "\t" << x_max << std::endl;

        auto i = std::floor((x - x_min) / dx);
        auto i_float = (x - x_min) / dx;
        auto j = std::floor((y - y_min) / dy);
        auto j_float = (y - y_min) / dy;
        auto a00 = data.get_data(i, j);
        auto a10 = data.get_data(i + 1, j) - data.get_data(i, j);
        auto a01 = data.get_data(i, j + 1) - data.get_data(i, j);
        auto a11 = data.get_data(i + 1, j + 1) + data.get_data(i, j) - data.get_data(i + 1, j) - data.get_data(i, j + 1);
        auto ix = i_float - i;
        auto jy = j_float - j;
        return a00 + a10 * ix + a01 * jy + a11 * ix * jy;
    }

    ior_field operator+(ior_field m){
        auto tmp = data.add_for_IOR_field(m.data);
        ior_field tmpp(tmp, this->dx, this->dy, this->x_min, this->x_max, this->y_min, this->y_max);
        return tmpp;
    }

};

