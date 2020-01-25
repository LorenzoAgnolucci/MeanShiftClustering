//
// Created by lorenzo on 27/12/19.
//

#ifndef MEANSHIFTCLUSTERING_CLUSTERMANAGER_H
#define MEANSHIFTCLUSTERING_CLUSTERMANAGER_H


#include <vector>

#include "Cluster.h"

class ClusterManager {

public:

    ClusterManager(std::vector<Point> &originalPoints, std::vector<Point> &shiftedPoints, float clusterEps);

    std::vector<Cluster> buildClusters();

    int getNumClusters();

    const std::vector<Cluster> &getClusters() const;

private:
    std::vector<Point> originalPoints;
    std::vector<Point> shiftedPoints;
    std::vector<Cluster> clusters;
    float clusterEps;
};


#endif //MEANSHIFTCLUSTERING_CLUSTERMANAGER_H
