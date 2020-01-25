#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>


#include "Point.h"
#include "MeanShift.h"
#include "ClusterManager.h"

int main() {

    std::string inputFileName = "/home/lorenzo/CLionProjects/MeanShiftClustering/datasets/data1.csv";

    std::vector<Point> points;

    std::ifstream data(inputFileName);
    std::string line;
    while (std::getline(data, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        std::vector<float> point;
        while (std::getline(lineStream, cell, ','))
            point.push_back(stod(cell));
        points.emplace_back(Point(point));
    }
    /*
    std::vector<Point> points = {{1, 1}, {0.5, 0.5}, {1.5, 1.5}, {2, 2}, {1.5, 2}, {2, 1.5}, {0.5, 1}, {1, 0.5},
                                 {0.0, 0.5}, {1.5, 1}, {11, 11}, {10.5, 10.5}, {11.5, 11.5}, {12, 12}, {11.5, 12}, {12, 11.5},
                                 {10.5, 11}, {11, 10.5}, {10.0, 10.5}, {11.5, 11}};
    */
    float bandwidth = 1.0;

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    std::vector<Point> shifted = meanShift(points, bandwidth);

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    float elapsedTime = std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();
    std::cout << "Elapsed time MeanShift: " << elapsedTime << " s" << std::endl;

//TODO: Togliere pragma da meanShift
//TODO: Capire bene come i parametri dipendano da bandwidth

    start = std::chrono::high_resolution_clock::now();

    ClusterManager clusterManager = ClusterManager(points, shifted, 0.4);
    clusterManager.buildClusters();
    int numClusters = clusterManager.getNumClusters();

    end = std::chrono::high_resolution_clock::now();
    elapsedTime = std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();
    std::cout << "Elapsed time ClusterManager: " << elapsedTime << " s" << std::endl;

    std::cout << "Number of clusters: " << numClusters << std::endl;

    std::string outputFileName = "/home/lorenzo/CLionProjects/MeanShiftClustering/output";
    std::ofstream outputFile(outputFileName + ".csv");
    int clusterId = 0;
    for (auto &cluster : clusterManager.getClusters()) {
        for (auto &point : cluster.getPoints()) {
            for (int i = 0; i < point.getNumDimensions(); i++) {
                float value = point.getValues()[i];
                outputFile << value << ",";
            }
            outputFile << clusterId << "\n";
        }
        ++clusterId;
    }


    return 0;
}
