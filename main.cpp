#include <iostream>

#include "Point.h"
#include "MeanShift.h"
#include "ClusterManager.h"

int main() {

    /*
    std::vector<Point> points;
    Point newPoint;

    newPoint = Point({1.0, 1.0});
    points.push_back(newPoint);

    newPoint = Point({2.0, 2.0});
    points.push_back(newPoint);

    newPoint = Point({4.0, 4.0});
    points.push_back(newPoint);

    newPoint = Point({1.4, 1.4});
    points.push_back(newPoint);
     */

    std::vector<Point> points = {{1, 1}, {0.5, 0.5}, {1.5, 1.5}, {2, 2}, {1.5, 2}, {2, 1.5}, {0.5, 1}, {1, 0.5},
                                 {0.0, 0.5}, {1.5, 1}, {11, 11}, {10.5, 10.5}, {11.5, 11.5}, {12, 12}, {11.5, 12}, {12, 11.5},
                                 {10.5, 11}, {11, 10.5}, {10.0, 10.5}, {11.5, 11}};

    float bandwidth = 1.0;

    std::vector<Point> shifted = meanShift(points, bandwidth);

    ClusterManager clusterManager = ClusterManager(points, shifted, 0.5);
    clusterManager.buildClusters();
    int numClusters = clusterManager.getNumClusters();

    std::cout << "Number of clusters: " << numClusters << std::endl;
    std::cout << "Shifted points: " << shifted[0].getValues()[0] << std::endl;


    return 0;
}
