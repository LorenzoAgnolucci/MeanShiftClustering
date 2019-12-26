//
// Created by lorenzo on 19/12/19.
//

#ifndef MIDTERM_PARALLEL_COMPUTING_UTILS_H
#define MIDTERM_PARALLEL_COMPUTING_UTILS_H

#include "Point.h"

#include <iostream>
#include <cmath>


float euclideanDistance(Point x, Point y){
    if (x.getNumDimensions() != y.getNumDimensions()){
        std::cout << "The points have a different number of dimensions" << std::endl;
        return 0;
    }
    float dist = 0.0;
    for (auto i = 0; i < x.getNumDimensions(); i++){
        dist += x.getValues()[i] - y.getValues()[i];
    }
    return std::sqrt(dist);
}


float gaussian(float distance, float bandwidth){
    return std::exp(-(distance * distance) / bandwidth);
}


#endif //MIDTERM_PARALLEL_COMPUTING_UTILS_H
