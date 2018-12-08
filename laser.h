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
        std::cout << x_min << "\t" << x_max << "\t" << y_min << "\t" << y_max << std::endl;
        while(true){
            std::cout << i++ << std::endl;
            auto vel_c = vel.back();
            auto dir_c = dir.get_last();
            // dir_c.print();
            std::cout << vel_c << std::endl;
            dir_c.print();
            auto new_point = loc.get_last() + vel_c * dir_c;
            auto near = new_point.get_near();
            new_point.print();
            // YOU HAVE TO MODIFY GET_NEAR FUNCTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            // INDEX AND COORDINATE SUCKS!!!!!!!!!!!!!!!!!!!
            std::cout << near[0].get_x() << "\t" << near[0].get_y() << "\t" << near[2].get_x() << "\t" <<  near[2].get_y() << std::endl;
            if(((near[0].get_x() > x_min && near[0].get_y() > y_min) && (near[2].get_x() < x_max && near[2].get_y() < y_max)) &&  (near[1].get_x() < x_max && near[3].get_x() > x_min)){
                loc.add_point(new_point);
            }
            else{break;}
        }
    }
    auto get_loc(){
        return loc;
    }

};


