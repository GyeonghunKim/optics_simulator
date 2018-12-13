// only convex lens only now!
#pragma once
#include "scalar_field.h"
#include "point2d.h"
#include <cmath>

class lens{
private:
    double center_x = 0, center_y = 0, param1, param2, // for spherical lens, param1 and 2 radius, for hyperbolic lens, param1 and 2 is focus length
            R_lens, d1, d2, d, thick, n;
    point2D<double> align = {0, 0};
    scalarField<double> lens_body();
    std::string lens_type;
public:
    // default constructor
    lens() = default;
    // default location is origin
    lens(double param1, double param2, double R_lens, double thick, double n, std::string lens_type){
        center_x = 0;
        center_y = 0;
        this->param1 = param1;
        this->param2 = param2;
        this->R_lens = R_lens;
        this->n = n;
        this->thick = thick;
        this->lens_type = lens_type;
        if(lens_type == "spherical_convex"){
            d1 = std::sqrt(param1 * param1 - R_lens * R_lens);
            d2 = -1 * std::sqrt(param2 * param2 - R_lens * R_lens);
            d = this->d1 - this->d2;
        }
        else if(lens_type == "parabolic_convex"){
            d1 = R_lens * R_lens / (4 * param1);
            d2 = R_lens * R_lens / (4 * param2);
            d = this->d1 + this->d2;
        }
        else if(lens_type == "spherical_concave") {
            d1 = param1 + thick / 2 - std::sqrt(param1 * param1 - R_lens * R_lens);
            d2 = param2 + thick / 2 - std::sqrt(param2 * param2 - R_lens * R_lens);
            d = this->d1 + this->d2;
        }
        align.set_x(1);
        align.set_y(0);
        align.normalize();
    }
    // default align is (1, 0)
    lens(double center_x, double center_y, double rad1, double rad2, double R_lens, double thick, double n, std::string lens_type){
        this->center_x = center_x;
        this->center_y = center_y;
        this->param1 = rad1;
        this->param2 = rad2;
        this->R_lens = R_lens;
        this->n = n;
        this->thick = thick;
        this->lens_type = lens_type;
        if(lens_type == "spherical_convex"){
            d1 = std::sqrt(param1 * param1 - R_lens * R_lens);
            d2 = -1 * std::sqrt(param2 * param2 - R_lens * R_lens);
            d = this->d1 - this->d2;
        }
        else if(lens_type == "parabolic_convex"){
            d1 = R_lens * R_lens / (4 * param1);
            d2 = R_lens * R_lens / (4 * param2);
            d = this->d1 + this->d2;
        }
        else if(lens_type == "spherical_concave") {
            d1 = param1 + thick / 2 - std::sqrt(param1 * param1 - R_lens * R_lens);
            d2 = param2 + thick / 2 - std::sqrt(param2 * param2 - R_lens * R_lens);
            d = this->d1 + this->d2;
        }
        align.set_x(1);
        align.set_y(0);
        align.normalize();
    }
    // most geenral constructor
    lens(double center_x, double center_y, double rad1, double rad2, double R_lens, double thick, double n, point2D<double> p, std::string lens_type){
        this->center_x = center_x;
        this->center_y = center_y;
        this->param1 = rad1;
        this->param2 = rad2;
        this->R_lens = R_lens;
        this->n = n;
        this->thick = thick;
        this->lens_type = lens_type;
        if(lens_type == "spherical_convex"){
            d1 = std::sqrt(param1 * param1 - R_lens * R_lens);
            d2 = -1 * std::sqrt(param2 * param2 - R_lens * R_lens);
            d = this->d1 - this->d2;
        }
        else if(lens_type == "parabolic_convex"){
            d1 = R_lens * R_lens / (4 * param1);
            d2 = R_lens * R_lens / (4 * param2);
            d = this->d1 + this->d2;
        }
        else if(lens_type == "spherical_concave") {
            d1 = param1 + thick / 2 - std::sqrt(param1 * param1 - R_lens * R_lens);
            d2 = param2 + thick / 2 - std::sqrt(param2 * param2 - R_lens * R_lens);
            d = this->d1 + this->d2;
        }
        align.set_x(p.get_x());
        align.set_y(p.get_y());
        align.normalize();
    }
    lens(double center_x, double center_y, double rad1, double rad2, double R_lens, double thick, double n, double align_x, double align_y, std::string lens_type){
        this->center_x = center_x;
        this->center_y = center_y;
        this->param1 = rad1;
        this->param2 = rad2;
        this->R_lens = R_lens;
        this->thick = thick;
        this->n = n;
        this->lens_type = lens_type;
        if(lens_type == "spherical_convex"){
            d1 = std::sqrt(param1 * param1 - R_lens * R_lens);
            d2 = -1 * std::sqrt(param2 * param2 - R_lens * R_lens);
            d = this->d1 - this->d2;
        }
        else if(lens_type == "parabolic_convex"){
            d1 = R_lens * R_lens / (4 * param1);
            d2 = R_lens * R_lens / (4 * param2);
            d = this->d1 + this->d2;
        }
        else if(lens_type == "spherical_concave") {
            d1 = param1 + thick / 2 - std::sqrt(param1 * param1 - R_lens * R_lens);
            d2 = param2 + thick / 2 - std::sqrt(param2 * param2 - R_lens * R_lens);
            d = this->d1 + this->d2;
        }
        align.set_x(align_x);
        align.set_y(align_y);
        align.normalize();
    }


    auto get_lens_type(){
        return lens_type;
    }
    // return theoretical focus(with paraxial approx.)
    double get_thin_focus(){
        return 1.0/((double(n) - 1.0) * (1.0/param1 - 1.0/param2));
    }

    //print spec of lens
    void print_spec(){
        std::cout << "lens_spec" << std::endl;
        std::cout << "center location: (" << center_x << ", " << center_y << ")" << std::endl;
        std::cout << "align direction: (" << align.get_x() << ", " << align.get_y() << ")" << std::endl;
        std::cout << "rad1 : " << param1 << std::endl;
        std::cout << "rad2 : " << param2 << std::endl;
        std::cout << "diameter : " << 2 * R_lens << std::endl;
        std::cout << "IOR: " << n << std::endl;
        std::cout << "thickness: " << d << "(" << d1 << " + " << d2 << " )" << std::endl;
        std::cout << "paraxial focus: " << get_thin_focus() << std::endl;
    }

    friend double lens_function(double, double, lens, std::string);
};


