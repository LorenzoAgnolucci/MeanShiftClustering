#include "MeanShift.h"

std::vector<Point> meanShift(const std::vector<Point> &points, float bandwidth, int numThreads) {

    std::vector<Point> shiftedPoints = points;

    for (int j = 0; j < NUM_ITERATIONS; j++) {
#pragma omp parallel for default(none) shared(points, bandwidth, shiftedPoints) schedule(static) num_threads(numThreads)
        for (int i = 0; i < points.size(); i++) {
            Point newPoint = shiftPoint(shiftedPoints[i], points, bandwidth);
            shiftedPoints[i] = newPoint;
        }
    }
    return shiftedPoints;
}


Point shiftPoint(const Point &oldPoint, const std::vector<Point> &allPoints, float bandwidth) {
    float totalWeight = 0.0;
    Point shiftedPoint(oldPoint.getNumDimensions());
    float distance;
    for (auto &point : allPoints){
        distance = euclideanDistance(oldPoint, point);
        float gaussian = gaussianKernel(distance, bandwidth);
        shiftedPoint += point * gaussian;
        totalWeight += gaussian;
    }

    shiftedPoint /= totalWeight;
    return shiftedPoint;
}
