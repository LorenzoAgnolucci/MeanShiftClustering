//
// Created by lorenzo on 19/12/19.
//

#ifndef MEANSHIFTCLUSTERING_UTILS_H
#define MEANSHIFTCLUSTERING_UTILS_H

#include "Point.h"

#include <iostream>
#include <cmath>


float euclideanDistance(const Point &x, const Point &y);


float gaussian_kernel(float distance, float bandwidth);


#endif //MEANSHIFTCLUSTERING_UTILS_H
