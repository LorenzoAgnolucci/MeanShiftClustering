//
// Created by lorenzo on 26/02/20.
//

#ifndef MEANSHIFTCLUSTERING_SPEEDUPTESTS_H
#define MEANSHIFTCLUSTERING_SPEEDUPTESTS_H

#include <iostream>
#include <omp.h>
#include <chrono>
#include <algorithm>
#include <experimental/filesystem>

#include "Point.h"
#include "ClusterManager.h"
#include "Utils.h"
#include "MeanShift.h"


#define BANDWIDTH 1.0
#define CLUSTER_EPS 1.0
#define NUM_TEST_ITERATIONS 1


void testDifferentSize(const std::string& inputPath, const std::string& outputPath);

void testDifferentClusters(const std::string& inputPath, const std::string& outputPath);

void testBandwidth(const std::string& inputPath, const std::string& outputPath);

void test(float bandwidth, const std::string& inputFileName, const std::string& outputClustersFileName, const std::string& outputTimeFileName);

#endif //MEANSHIFTCLUSTERING_SPEEDUPTESTS_H
