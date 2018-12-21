#pragma once
#include "point2d.h"

class laser_device{
private:
    point2D<double> loc = {0,0};
    point2D<double> dir = {0,0};
public:
    laser_device() = default;
    laser_device(point2D<double> loc, point2D<double> dir) : loc(loc), dir(dir){}
    laser_device(double loc_x, double loc_y, double dir_x, double dir_y){
        loc.set_x(loc_x);
        loc.set_y(loc_y);
        dir.set_x(dir_x);
        dir.set_y(dir_y);
    }
    auto get_loc(){
        return loc;
    }
    auto get_dir(){
        return dir;
    }
    auto get_loc_x(){
        return loc.get_x();
    }
    auto get_loc_y(){
        return loc.get_y();
    }
    auto get_dir_x(){
        return dir.get_x();
    }
    auto get_dir_y(){
        return dir.get_y();
    }
    std::string get_loc_str()
    {
        return "(" + std::to_string(loc.get_x()) + ", " + std::to_string(loc.get_y()) + ")";
    }
    std::string get_align_str()
    {
        return "(" + std::to_string(dir.get_x()) + ", " + std::to_string(dir.get_y()) + ")";
    }
};
