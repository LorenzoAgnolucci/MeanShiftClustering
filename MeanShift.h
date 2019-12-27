//
// Created by lorenzo on 27/12/19.
//

#ifndef MEANSHIFTCLUSTERING_MEANSHIFT_H
#define MEANSHIFTCLUSTERING_MEANSHIFT_H

#include "Point.h"

#include <vector>

#define RADIUS 0.5
#define MAX_ITERATIONS 5
#define SHIFTING_EPS 0.01

std::vector<Point> meanShift(const std::vector<Point> &points, float bandwidth);

Point shiftPoint(const Point &oldPoint, const std::vector<Point> &allPoints, float bandwidth);

#endif //MEANSHIFTCLUSTERING_MEANSHIFT_H
