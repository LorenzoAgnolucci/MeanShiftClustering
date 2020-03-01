//
// Created by lorenzo on 26/12/19.
//

#include "MeanShift.h"

#include <algorithm>


std::vector<Point> meanShift(const std::vector<Point> &points, float bandwidth, int numThreads) {

    int numIterations = 0;
    std::vector<Point> shiftedPoints = points;
    std::vector<bool> still_shifting = std::vector<bool>(points.size(), true);
    while (!std::none_of(still_shifting.begin(), still_shifting.end(), [](bool v){return v;}) && numIterations <= MAX_ITERATIONS) {
#pragma omp parallel for default(none) shared(points, bandwidth, still_shifting, shiftedPoints) schedule(dynamic) num_threads(numThreads)


        for (int i = 0; i < points.size(); ++i) {
            if (!still_shifting[i]) {
                continue;
            }

            Point newPoint = shiftPoint(shiftedPoints[i], points, bandwidth);

            if (euclideanDistance(newPoint, points[i]) >= SHIFTING_EPS){
                shiftedPoints[i] = newPoint;
            }
            else {
                still_shifting[i] = false;
            }
        }
        numIterations++;
    }

    if(numIterations == MAX_ITERATIONS){
        std::cout << "WARNING: reached the maximum number of iterations" << std::endl;
    }

    return shiftedPoints;
}


Point shiftPoint(const Point &oldPoint, const std::vector<Point> &allPoints, float bandwidth) {
    float totalWeight = 0.0;
    Point shiftedPoint(oldPoint.getNumDimensions());
    float distance;
    for (auto &point : allPoints){
        distance = euclideanDistance(oldPoint, point);
        if(distance <= RADIUS){
            float gaussian = gaussian_kernel(distance, bandwidth);
            shiftedPoint += point * gaussian;
            totalWeight += gaussian;
        }
    }

    shiftedPoint /= totalWeight;
    return shiftedPoint;
}
