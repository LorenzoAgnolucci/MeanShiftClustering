//
// Created by lorenzo on 27/12/19.
//

#ifndef MEANSHIFTCLUSTERING_MEANSHIFT_H
#define MEANSHIFTCLUSTERING_MEANSHIFT_H

#include "Point.h"
#include "Utils.h"

#define RADIUS 3
#define MAX_ITERATIONS 10
#define SHIFTING_EPS 0.004

std::vector<Point> meanShift(const std::vector<Point> &points, float bandwidth, int numThreads=1);

Point shiftPoint(const Point &oldPoint, const std::vector<Point> &allPoints, float bandwidth);

#endif //MEANSHIFTCLUSTERING_MEANSHIFT_H
