#include "lens.h"
#include <cmath>

double lens_function(double x, double y, lens l, std::string lens_type){
    if(lens_type == "spherical_convex"){
        double r1 = std::sqrt((x - l.d1 * l.align.get_x() - l.center_x) * (x - l.d1 * l.align.get_x() - l.center_x)
                              + (y - l.d1 * l.align.get_y() - l.center_y) * (y - l.d1 * l.align.get_y() - l.center_y));
        double r2 = std::sqrt((x - l.d2 * l.align.get_x() - l.center_x) * (x - l.d2 * l.align.get_x() - l.center_x)
                              + (y - l.d2 * l.align.get_y() - l.center_y) * (y - l.d2 * l.align.get_y() - l.center_y));
        if (r1 < std::abs(l.param1) && r2 < std::abs(l.param2)){
            return l.n;
        }
        else{
            return 1;
        }
    }
    else if(lens_type == "parabolic_convex"){
        double theta = std::atan(l.align.get_y() / l.align.get_x());
        x -= l.center_x;
        y -= l.center_y;
        double lhs1 = (x * std::sin(theta) - y * std::cos(theta)) * (x * std::sin(theta) - y * std::cos(theta));
        double rhs1 = 4 * l.param1 * (x * std::cos(theta) + y * std::sin(theta) + l.d1);
        double lhs2 = (x * std::sin(theta) - y * std::cos(theta)) * (x * std::sin(theta) - y * std::cos(theta));
        double rhs2 = -4 * l.param2 * (x * std::cos(theta) + y * std::sin(theta) - l.d1);
        if (lhs1 < rhs1 && lhs2 < rhs2){
            return l.n;
        }
        else{
            return 1;
        }
    }
    else if(lens_type == "spherical_concave") {
        double theta = std::atan(l.align.get_y() / l.align.get_x());
        double x1 = l.center_x - l.d1 * std::cos(theta) + l.R_lens * std::sin(theta);
        double y1 = l.center_y - l.d1 * std::sin(theta) - l.R_lens * std::cos(theta);
        double x2 = l.center_x + l.d2 * std::cos(theta) + l.R_lens * std::sin(theta);
        double y2 = l.center_y + l.d2 * std::sin(theta) - l.R_lens * std::cos(theta);

        double lin_lhs1 = (y - y1) * (x1 - x2) * (x1 - x2);
        double lin_rhs1 = (y1 - y2) * (x - x1) * (x1 - x2);

        if(lin_lhs1 >= lin_rhs1){
            double x3 = l.center_x + l.d2 * std::cos(theta) - l.R_lens * std::sin(theta);
            double y3 = l.center_y + l.d2 * std::sin(theta) + l.R_lens * std::cos(theta);
            double x4 = l.center_x - l.d1 * std::cos(theta) - l.R_lens * std::sin(theta);
            double y4 = l.center_y - l.d1 * std::sin(theta) + l.R_lens * std::cos(theta);

            double lin_lhs2 = (y - y4) * (x4 - x3) * (x4 - x3);
            double lin_rhs2 = (y4 - y3) * (x - x4) * (x4 - x3);

            if(lin_lhs2 <= lin_rhs2){
                double lin_lhs3 = (y - y1) * (x1 - x4) * (x1 - x4);
                double lin_rhs3 = (y1 - y4) * (x - x1) * (x1 - x4);
                double lin_lhs4 = (y - y3) * (x2 - x3) * (x2 - x3);
                double lin_rhs4 = (y2 - y3) * (x - x3) * (x2 - x3);
                if(lin_lhs3 >= lin_rhs3 && lin_lhs4 <= lin_rhs4){
                    if(x1 == x4){
                        if(!(x >= x1 && x <= x2)){return 1;}
                    }
                    double xc1 = l.center_x - (l.param1 + l.thick / 2) * std::cos(theta);
                    double yc1 = l.center_y - (l.param1 + l.thick / 2) * std::sin(theta);
                    double xc2 = l.center_x + (l.param2 + l.thick / 2) * std::cos(theta);
                    double yc2 = l.center_y + (l.param2 + l.thick / 2) * std::sin(theta);
                    double r1_square = (x - xc1) * (x - xc1) + (y - yc1) * (y - yc1);
                    double r2_square = (x - xc2) * (x - xc2) + (y - yc2) * (y - yc2);
                    if(r1_square > l.param1 * l.param1 && r2_square > l.param2 * l.param2){
                        return l.n;
                    }
                    else{
                        return 1;
                    }
                }
                else{
                    return 1;
                }
            }
            else{
                return 1;
            }
        }
        else{
            return 1;
        }
    }
    else if(lens_type == "gaussian"){   // in this case, param1 = sigma_x of gaussian and param2 = sigma_y
        auto amp = l.n - 1;
        return 1 + amp * std::exp(-(x - l.center_x) * (x - l.center_x) / (2 * l.param1 * l.param1) - (y - l.center_y) * (y - l.center_y) / (2 * l.param2 * l.param2));
    }
    else if(lens_type == "mirage"){   // in this case, param1 = mean_value, param2 = gradient of IOR
        double tmp = l.param1 - l.param2 * (y - l.center_y);
        if (tmp < 1) return 1;
        else return tmp;
    }
    else if(lens_type == "comp"){   // I don't know how real compressed lens act. so I just composite gaussian and sperical concave lens
        // std::cout << "in comp" << std::endl;
        auto d1 = std::sqrt(l.param1 * l.param1 - l.R_lens * l.R_lens);
        auto d2 = -1 * std::sqrt(l.param2 * l.param2 - l.R_lens * l.R_lens);

        double amp = 0.5;
        double r1 = std::sqrt((x - d1 * l.align.get_x() - l.center_x) * (x - d1 * l.align.get_x() - l.center_x)
                              + (y - d1 * l.align.get_y() - l.center_y) * (y - d1 * l.align.get_y() - l.center_y));
        double r2 = std::sqrt((x - d2 * l.align.get_x() - l.center_x) * (x - d2 * l.align.get_x() - l.center_x)
                              + (y - d2 * l.align.get_y() - l.center_y) * (y - d2 * l.align.get_y() - l.center_y));
        if (r1 < std::abs(l.param1) && r2 < std::abs(l.param2)){
            return l.n + amp * std::exp(-(x - l.center_x) * (x - l.center_x)/2 - (y - l.center_y) * (y - l.center_y)/5);
        }
        else{
            return 1;
        }
    }

}
