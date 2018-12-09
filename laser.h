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
        // table.print();
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

        while(true){
            // std::cout << "i = " << i++ << std::endl;
            auto vel_c = vel.back();
            auto dir_c = dir.get_last();
            auto new_point = loc.get_last() + vel_c * dir_c * dt;
            auto near = new_point.get_near();
            if((new_point.get_x() > x_min && new_point.get_y() > y_min) && (new_point.get_x() < x_max && new_point.get_y() < y_max)){
                std::cout << "I'm in!!" <<std::endl;
                loc.add_point(new_point);
            }

            else{break;}
        }
    }
    auto get_loc(){
        return loc;
    }

};


