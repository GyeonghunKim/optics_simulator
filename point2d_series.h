#pragma once
#include "point2d.h"


template <typename T>
class point2D_series {
private:
    // point2D_series is vector of point2D
    std::vector<point2D<T>> data;
    int length = 0;
public:
    // constructors
    point2D_series() = default;
    // initialize with length
    point2D_series(int length){
        data.resize(length);
        this->length = length;
    }
    // initialize with length and one value
    point2D_series(int length, point2D<T> value){
        data.resize(length, value);
        this->length = length;
    }
    // initialize with vector of point2D
    point2D_series(std::vector<point2D<T>> v){
        data = v;
        this->length = v.size();
    }
    // add one point2D in vector
    void add_point(const point2D<T> p){
        data.push_back(p);
        this->length ++;
    }
    // print
    void print(){
        std::cout << "(" << std::endl;
        for(auto i = 0; i < length; ++i){
            std::cout << i << ": ";
            data[i].print();
        }
        std::cout << ")" << std::endl;
    }
    // getters
    auto get_last(){
        return data.back();
    }
    auto get_data(){
        return data;
    }
    auto get_length(){
        return length;
    }
};
