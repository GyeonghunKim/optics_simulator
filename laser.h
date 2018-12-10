#pragma once
#include "point2d.h"
#include "point2d_series.h"
#include "scalar_field.h"
#include "ior_field.h"

class laser
{
private:
    // photon location
    point2D_series<double> loc;
    // photon direction
    point2D_series<double> dir;
    // photon velocity
    std::vector<double> vel;
    // information of optical table(ior field)
    int N_rows, N_cols;
    double x_min, x_max, y_min, y_max;
    // time scale
    double dt;
    // ior_field
    matrix<double> table;
    // velocity at n = 1
    double c = 1;
    // ior_field table
    ior_field IOR_field;
public:
    // default constructor
    laser() = default;

    // constructor
    laser(point2D<double> loc, point2D<double> dir, ior_field opt, double dt = 1){
        this->loc.add_point(loc);
        this->dir.add_point(dir);
        this->vel.push_back(c);
        this->N_rows = opt.get_N_row();
        this->N_cols = opt.get_N_col();
        this->x_min = opt.get_x_min();
        this->x_max = opt.get_x_max();
        this->y_min = opt.get_y_min();
        this->y_max = opt.get_y_max();
        this->dt = dt;
        this->table = opt.get_data();
        this->IOR_field = opt;
        std::cout << "This is from constructor" << std::endl;
        std::cout << opt.get_dx() << std::endl;

    }

    // get IOR using interpolation
    auto get_IOR(point2D<double> p){
        auto nears = p.get_near();
        auto weights = p.get_weight();
        auto n = 0.0;
        for(auto i = 0; i< 4; ++i){
            std::cout << table.get_data(nears[i]) << std::endl;
            n += weights[i] * table.get_data(nears[i]);
        }
        return n;
    }

    // get velocity using definition of IOR v = c / n
    auto get_vel(point2D<double> p){
        return c / get_IOR(p);
    }



    void activation(){
        int i = 0;
        auto s_field_ior = scalarField<double>(IOR_field.get_data(), IOR_field.get_dx(), IOR_field.get_dy());
        auto grad_ior_field = get_gradient(s_field_ior);
        // grad_ior_field.print();
        auto dx = IOR_field.get_dx();
        std::cout << "dx = " << dx << std::endl;
        auto dy = IOR_field.get_dy();
        int k = 1;
        int kk = 1;
        while(true){
            // std::cout << "i = " << i++ << std::endl;
            auto vel_c = vel.back();
            auto dir_c = dir.get_last();

            auto i = (loc.get_last().get_x() - x_min)/dx;
            auto j = (loc.get_last().get_y() - y_min)/dy;

            auto tp_x = grad_ior_field.get_x_field().get_data(i, j);
            auto tp_y = grad_ior_field.get_y_field().get_data(i, j);

            auto new_point = loc.get_last() + vel_c * dir_c * dt;

            auto near = new_point.get_near();

            if(tp_x == 0 && tp_y == 0){
                dir.add_point(dir_c);
            }
            else{
                dir_c.set_y(dir_c.get_y() + 0.3);
                dir.add_point(dir_c);
            }

            if((new_point.get_x() > x_min && new_point.get_y() > y_min) && (new_point.get_x() < x_max && new_point.get_y() < y_max)){
                loc.add_point(new_point);
            }
            else{break;}
        }
    }
    auto get_loc(){
        return loc;
    }

};


