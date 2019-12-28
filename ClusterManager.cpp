//
// Created by lorenzo on 27/12/19.
//

#include "ClusterManager.h"
#include "Utils.h"


ClusterManager::ClusterManager(std::vector<Point> &originalPoints, std::vector<Point> &shiftedPoints, float clusterEps){
    this->originalPoints = originalPoints;
    this->shiftedPoints = shiftedPoints;
    this->clusterEps = clusterEps;
}

std::vector<Cluster> ClusterManager::buildClusters(){

    for (int i = 0; i < originalPoints.size(); ++i) {
        auto iter = clusters.begin();
        auto iterEnd = clusters.end();
        while(iter != iterEnd){
            if (euclideanDistance(iter->getCentroid(), shiftedPoints[i]) <= clusterEps){
                iter->addPoint(originalPoints[i]);
                break;
            }
            iter++;
        }
        if(iter == iterEnd){
            Cluster newCluster(shiftedPoints[i]);
            newCluster.addPoint(originalPoints[i]);
            clusters.push_back(newCluster);
        }
    }

    return clusters;
}

int ClusterManager::getNumClusters(){
    return clusters.size();
}