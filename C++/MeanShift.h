#ifndef MEANSHIFTCLUSTERING_MEANSHIFT_H
#define MEANSHIFTCLUSTERING_MEANSHIFT_H

#include "Point.h"
#include "Utils.h"

#define NUM_ITERATIONS 10

std::vector<Point> meanShift(const std::vector<Point> &points, float bandwidth, int numThreads=1);

Point shiftPoint(const Point &oldPoint, const std::vector<Point> &allPoints, float bandwidth);

#endif //MEANSHIFTCLUSTERING_MEANSHIFT_H
