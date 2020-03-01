//
// Created by lorenzo on 27/12/19.
//

#ifndef MEANSHIFTCLUSTERING_CLUSTER_H
#define MEANSHIFTCLUSTERING_CLUSTER_H


#include <vector>
#include <iostream>

#include "Point.h"

class Cluster {

public:

    explicit Cluster(Point &centroid) {
        this->centroid = std::move(centroid);
        this->shiftedPoints.push_back(this->centroid);
    }

    void addOriginalPoint(const Point &point){
        originalPoints.push_back(point);
    }

    void addShiftedPoint(const Point &point){
        shiftedPoints.push_back(point);
        computeCentroid();
    }

    const std::vector<Point> &getShiftedPoints() const {
        return shiftedPoints;
    }

    const std::vector<Point> &getOriginalPoints() const {
        return originalPoints;
    }

    const Point &getCentroid() const {
        return centroid;
    }

    void computeCentroid();

private:
    std::vector<Point> originalPoints;
    std::vector<Point> shiftedPoints;
    Point centroid;
};


#endif //MEANSHIFTCLUSTERING_CLUSTER_H
