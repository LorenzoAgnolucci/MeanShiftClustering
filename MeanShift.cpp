//
// Created by lorenzo on 26/12/19.
//

#include "Point.h"
#include "Utils.h"
#include "MeanShift.h"

#include <vector>


std::vector<Point> meanShift(const std::vector<Point> &points, float bandwidth){

    int numIterations = 0;
    std::vector<Point> shiftedPoints = points;
    std::vector<bool> still_shifting = std::vector<bool>(points.size(), true);

    while (numIterations <= MAX_ITERATIONS) {
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

    return points;
}


Point shiftPoint(const Point &oldPoint, const std::vector<Point> &allPoints, float bandwidth) {
    float totalWeight = 0.0;
    Point shiftedPoint(oldPoint.getNumDimensions());
    float distance;
    for (auto &point : allPoints){
        distance = euclideanDistance(oldPoint, point);
        if(distance <= RADIUS){
            float gaussian = gaussian_kernel(distance, bandwidth);
            shiftedPoint += oldPoint * gaussian;
            totalWeight += gaussian;
        }
    }

    shiftedPoint /= totalWeight;
    return shiftedPoint;
}
