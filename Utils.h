//
// Created by lorenzo on 19/12/19.
//

#ifndef MEANSHIFTCLUSTERING_UTILS_H
#define MEANSHIFTCLUSTERING_UTILS_H

#include "Point.h"
#include "ClusterManager.h"

#include <iostream>
#include <cmath>


float euclideanDistance(const Point &x, const Point &y);

float gaussian_kernel(float distance, float bandwidth);

std::vector<Point> readPointsFromCSV(const std::string& fileName);

void writeClustersToCSV(const std::string& fileName, const ClusterManager& clusterManager);

void writeTimeToCSV(const std::string& fileName, int numThreads, float time, int numPoints, int dimensions, int numClusters, float bandwidth);

#endif //MEANSHIFTCLUSTERING_UTILS_H
