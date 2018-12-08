#pragma once
#include "scalar_field.h"
#include "point2d.h"
#include <cmath>

class lens{
private:
    double center_x = 0, center_y = 0, rad1, rad2, R_lens, d1, d2, d, n;
    point2D<double> align = {0, 0};
    scalarField<double> lens_body();
public:
    // default constructor
    lens() = default;
    // default location is origin
    lens(double rad1, double rad2, double R_lens, double n){
        center_x = 0;
        center_y = 0;
        this->rad1 = rad1;
        this->rad2 = rad2;
        this->R_lens = R_lens;
        this->n = n;
        d1 = -1 * std::sqrt(rad1 * rad1 - R_lens * R_lens);
        d2 = std::sqrt(rad2 * rad2 - R_lens * R_lens);
        d = this->d1 + this->d2;
        align.set_x(1);
        align.set_y(0);
        align.normalize();
    }
    // default align is (1, 0)
    lens(double center_x, double center_y, double rad1, double rad2, double R_lens, double n){
        this->center_x = center_x;
        this->center_y = center_y;
        this->rad1 = rad1;
        this->rad2 = rad2;
        this->R_lens = R_lens;
        this->n = n;
        d1 = -1 * std::sqrt(rad1 * rad1 - R_lens * R_lens);
        d2 = std::sqrt(rad2 * rad2 - R_lens * R_lens);
        d = this->d1 + this->d2;
        align.set_x(1);
        align.set_y(0);
        align.normalize();
    }
    // most geenral constructor
    lens(double center_x, double center_y, double rad1, double rad2, double R_lens, double n, point2D<double> p){
        this->center_x = center_x;
        this->center_y = center_y;
        this->rad1 = rad1;
        this->rad2 = rad2;
        this->R_lens = R_lens;
        this->n = n;
        d1 = -1 * std::sqrt(rad1 * rad1 - R_lens * R_lens);
        d2 = std::sqrt(rad2 * rad2 - R_lens * R_lens);
        d = this->d1 + this->d2;
        align.set_x(p.get_x());
        align.set_y(p.get_y());
        align.normalize();
    }

    // return theoretical focus(with co-axial approx.)
    double get_thin_focus(){
        return 1/((this->n - 1) * (1/this->rad1 - 1/this->rad2));
    }

    //print spec of lens
    void print_spec(){
        std::cout << "lens_spec" << std::endl;
        std::cout << "center location: (" << center_x << ", " << center_y << ")" << std::endl;
        std::cout << "align direction: (" << align.get_x() << ", " << align.get_y() << ")" << std::endl;
        std::cout << "rad1 : " << rad1 << std::endl;
        std::cout << "rad2 : " << rad2 << std::endl;
        std::cout << "diameter : " << 2 * R_lens << std::endl;
        std::cout << "IOR: " << n << std::endl;
        std::cout << "thickness: " << d << "(" << d1 << " + " << d2 << " )" << std::endl;
    }

    // friend double lens_function(double, double, lens);
};

