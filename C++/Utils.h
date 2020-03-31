#ifndef MEANSHIFTCLUSTERING_UTILS_H
#define MEANSHIFTCLUSTERING_UTILS_H

#include "Point.h"
#include "ClusterManager.h"

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <experimental/filesystem>


float euclideanDistance(const Point &x, const Point &y);

float gaussianKernel(float distance, float bandwidth);

std::vector<Point> readPointsFromCSV(const std::string& fileName);

void writeClustersToCSV(const std::string& fileName, const ClusterManager& clusterManager);

void writeTimeToCSV(const std::string& fileName, int numThreads, float time, int numPoints, int dimensions, int numClusters, float bandwidth);

#endif //MEANSHIFTCLUSTERING_UTILS_H
