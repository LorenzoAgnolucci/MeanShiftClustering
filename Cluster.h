//
// Created by lorenzo on 27/12/19.
//

#ifndef MEANSHIFTCLUSTERING_CLUSTER_H
#define MEANSHIFTCLUSTERING_CLUSTER_H


#include <vector>

#include "Point.h"

class Cluster {

public:

    explicit Cluster(Point &centroid) {
        this->centroid = std::move(centroid);
    }

    void addPoint(const Point &point){
        points.push_back(point);
    }

    const std::vector<Point> &getPoints() const {
        return points;
    }

    const Point &getCentroid() const {
        return centroid;
    }

private:
    std::vector<Point> points;
    Point centroid;
};


#endif //MEANSHIFTCLUSTERING_CLUSTER_H
