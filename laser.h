#pragma once
#include "point2d.h"
#include "point2d_series.h"
#include "scalar_field.h"
#include "ior_field.h"
#include "vector_field.h"
#include "laser_device.h"

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
    // velocity
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
        std::cout << opt.get_x_min() << "\t" << opt.get_y_min() << std::endl;
    }

    laser(laser_device dev, ior_field opt, double dt = 1){
        this->loc.add_point(dev.get_loc());
        this->dir.add_point(dev.get_dir());
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
        std::cout << opt.get_x_min() << "\t" << opt.get_y_min() << std::endl;
    }


    // get IOR using interpolation
    auto get_IOR(point2D<double> p){
        auto dx = IOR_field.get_dx();
        auto dy = IOR_field.get_dy();
        auto nears = p.get_near(x_min, y_min, dx, dy);
        auto weights = p.get_weight();
        auto n = 0.0;
        for(auto i = 0; i< 4; ++i){
            // std::cout << table.get_data(nears[i]) << std::endl;
            n += weights[i] * table.get_data(nears[i]);
        }
        return n;
    }
    auto get_IOR2(point2D<double> p){
        // std::cout << IOR_field.get_x_min() << "\t" << IOR_field.get_x_max() << std::endl;
        return IOR_field.get_value_bilinear(p.get_x(), p.get_y());
    }

    // get velocity using definition of IOR v = c / n
    auto get_vel(point2D<double> p){
        return c / get_IOR(p);
    }


    void activation(int number_smoothing = 1){
        auto s_field_ior = scalarField<double>(IOR_field.get_data(), IOR_field.get_dx(), IOR_field.get_dy());
        s_field_ior.box_smoothing(number_smoothing);
        auto grad_ior_field = get_gradient<double>(s_field_ior);
        auto dx = IOR_field.get_dx();
        auto dy = IOR_field.get_dy();
        while(true){

            auto vel_c = vel.back();
            auto dir_c = dir.get_last();
            auto loc_c = loc.get_last();
            auto near = loc_c.get_near(x_min, y_min, dx, dy);
            auto weights = loc_c.get_weight();
            auto new_point = loc_c + vel_c * dir_c * dt;


            double tp_x = 0;
            double tp_y = 0;
            auto grad_ior_x = grad_ior_field.get_x_field();
            auto grad_ior_y = grad_ior_field.get_y_field();
            tp_x += grad_ior_x.get_data(near[0].get_x(), near[0].get_y()) * weights[0];
            tp_x += grad_ior_x.get_data(near[1].get_x(), near[1].get_y()) * weights[1];
            tp_x += grad_ior_x.get_data(near[2].get_x(), near[2].get_y()) * weights[2];
            tp_x += grad_ior_x.get_data(near[3].get_x(), near[3].get_y()) * weights[3];

            tp_y += grad_ior_y.get_data(near[0].get_x(), near[0].get_y()) * weights[0];
            tp_y += grad_ior_y.get_data(near[1].get_x(), near[1].get_y()) * weights[1];
            tp_y += grad_ior_y.get_data(near[2].get_x(), near[2].get_y()) * weights[2];
            tp_y += grad_ior_y.get_data(near[3].get_x(), near[3].get_y()) * weights[3];

            if(tp_x == 0 && tp_y == 0){
                dir.add_point(dir_c);
            }
            else{

                point2D<double> grad_c = {tp_x, tp_y};
                grad_c.normalize();
                auto tang_c = grad_c.rotate_halfpi();
                dir_c.normalize();

                auto thetai = grad_c.get_theta(dir_c);
                auto cos_thetai = std::cos(thetai);
                auto sin_thetaf = get_IOR2(loc_c) * std::sqrt(1 - cos_thetai * cos_thetai) / get_IOR2(new_point);
                // std::cout << sin_thetaf << std::endl;
                double thetaf = 0;
                if(thetai > 0){
                    thetaf = std::abs(std::asin(sin_thetaf));
                }
                else{
                    thetaf = -1 * std::abs(std::asin(sin_thetaf));
                }
                if (std::isnan(thetaf)){
                    auto new_dir = grad_c.rotate_halfpi();
                    dir.add_point(new_dir);
                    if((new_point.get_x() > x_min * 1.1 && new_point.get_y() > y_min * 1.1) && (new_point.get_x() < x_max * 0.9 && new_point.get_y() < y_max * 0.9)){
                        loc.add_point(new_point);
                        continue;
                    }
                    else{break;}
                    std::cout << "program stopped because thetaf is nan" << std::endl;
                    std::cout << "IOR loc_c is: " << get_IOR2(loc_c) << std::endl;
                    std::cout << "IOR new_point is: " << get_IOR2(new_point) << std::endl;
                    break;
                }
                std::cout << "loc is : " << std::endl;
                loc_c.print_only_value();
                std::cout << "grad is : " << std::endl;
                grad_c.print_only_value();
                std::cout << "thetaf is: " << thetaf << std::endl;
                if(std::abs(thetai) > std::atan(1) * 2){
                    if(thetaf > 0){
                        std::cout << "****************1********************" << std::endl;
                        auto new_dir = grad_c.rotate(4 * std::atan(1) - thetaf);
                        dir.add_point(new_dir);
                    }
                    else{
                        std::cout << "****************2********************" << std::endl;
                        auto new_dir = grad_c.rotate(4 * std::atan(1) - thetaf);
                        dir.add_point(new_dir);
                    }
                }
                else{
                     std::cout << "****************3********************" << std::endl;
                    auto new_dir = grad_c.rotate(thetaf);
                    dir.add_point(new_dir);
                }
            }
            if((new_point.get_x() > x_min * 1.1 && new_point.get_y() > y_min * 1.1) && (new_point.get_x() < x_max * 0.9 && new_point.get_y() < y_max * 0.9)){
                loc.add_point(new_point);
            }
            else{break;}
        }
    }
    auto get_loc(){
        return loc;
    }

};


