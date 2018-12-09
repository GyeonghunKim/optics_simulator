#include "lens.h"
double lens_function(double x, double y, lens l){
    double r1 = std::sqrt((x - l.d1 * l.align.get_x() - l.center_x) * (x - l.d1 * l.align.get_x() - l.center_x)
                          + (y - l.d1 * l.align.get_y() - l.center_y) * (y - l.d1 * l.align.get_y() - l.center_y));
    double r2 = std::sqrt((x - l.d2 * l.align.get_x() - l.center_x) * (x - l.d2 * l.align.get_x() - l.center_x)
                          + (y - l.d2 * l.align.get_y() - l.center_y) * (y - l.d2 * l.align.get_y() - l.center_y));
    if (r1 < std::abs(l.rad1) && r2 < std::abs(l.rad2)){
        return l.n;
    }
    else{
        return 1;
    }
}

