//
// Created by lorenzo on 27/12/19.
//

#include "Utils.h"

float euclideanDistance(const Point &x, const Point &y) {
    if (x.getNumDimensions() != y.getNumDimensions()) {
        std::cout << "The points have a different number of dimensions" << std::endl;
        return 0;
    }
    float dist = 0.0;
    for (auto i = 0; i < x.getNumDimensions(); i++) {
        dist += powf(x.getValues()[i] - y.getValues()[i], 2);
    }
    return std::sqrt(dist);
}

float gaussian_kernel(float distance, float bandwidth){
    return std::exp(-(distance * distance) / (2 * powf(bandwidth, 2)));
}

