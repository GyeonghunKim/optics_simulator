#pragma once
#include <iostream>
#include <vector>
#include <cmath>

template <typename T>
class point2D
{
private:
    T x;
    T y;
public:
    // point2D default constructor
    point2D() = default;
    // initialize point2D with two coordinate
    point2D(T x = 0, T y = 0) : x(x), y(y) {}
    // operator overloadings
    point2D operator+(const point2D& p){
        point2D tmp(x + p.x, y + p.y);
        return tmp;
    }

    point2D operator-(const point2D& p){
        point2D tmp(x - p.x, y - p.y);
        return tmp;
    }

    point2D operator*(const T c){
        point2D tmp(x * c, y * c);
        return tmp;
    }

    friend point2D operator*(const T c, point2D & p){
        return p * c;
    }
    // getters
    auto get_x(){
        return x;
    }

    auto get_y(){
        return y;
    }
    // setters
    void set_x(double x){
        this->x = x;
    }

    void set_y(double y){;
        this->y = y;
    }

    // functions about size of point
    double norm2(){
        return std::sqrt(x * x + y * y);

    }
    void normalize(){
        auto norm2 = std::sqrt(x * x + y * y);
        x /= norm2;
        y /= norm2;
    }

    // functions for interpolation
    // return near integer points in order below.
    // 0 1
    // 3 2
    auto get_near(){    // return type is std::vector<point2D<int>> with size 4
        std::vector<point2D<int>> near_points;
        point2D<int> tmp1(floor(x), floor(y));
        near_points.push_back(tmp1);
        point2D<int> tmp2(floor(x) + 1, floor(y));
         near_points.push_back(tmp2);
        point2D<int> tmp3(floor(x) + 1, floor(y) + 1);
         near_points.push_back(tmp3);
        point2D<int> tmp4(floor(x), floor(y) + 1);
         near_points.push_back(tmp4);
        return near_points;
    }
    // return inverse distance weight
    // refer below wiki document
    // https://en.wikipedia.org/wiki/Inverse_distance_weighting

    auto get_weight(double p = 1){
        std::vector<double> weights(0, 0);
        point2D<double> tmp1(floor(x), floor(y));
        auto dp1 = *this - tmp1;
        auto d1 = dp1.norm2();

        point2D<double> tmp2(floor(x), floor(y));
        auto dp2 = *this - tmp2;
        auto d2 = dp2.norm2();

        point2D<double> tmp3(floor(x), floor(y));
        auto dp3 = *this - tmp3;
        auto d3 = dp3.norm2();

        point2D<double> tmp4(floor(x), floor(y));
        auto dp4 = *this - tmp4;
        auto d4 = dp4.norm2();

        auto w1 = 1.0 / std::pow(d1, p)
        auto w2 = 1.0 / std::pow(d2, p)
        auto w3 = 1.0 / std::pow(d3, p)
        auto w4 = 1.0 / std::pow(d4, p)
        auto w_sum = w1 + w2 + w3 + w4

        weights.push_back(w1 / w_sum);
        weights.push_back(w2 / w_sum);
        weights.push_back(w3 / w_sum);
        weights.push_back(w4 / w_sum);

        return weights;
    }
};

