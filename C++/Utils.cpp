#include "Utils.h"

float euclideanDistance(const Point &x, const Point &y) {
    if (x.getNumDimensions() != y.getNumDimensions()) {
        std::cout << "The points have a different number of dimensions" << std::endl;
        return 0;
    }
    float dist = 0.0;
    for (auto i = 0; i < x.getNumDimensions(); i++) {
        dist += powf(x.getValues()[i] - y.getValues()[i], 2);
    }
    return std::sqrt(dist);
}

float gaussianKernel(float distance, float bandwidth){
    return std::exp(-(distance * distance) / (2 * powf(bandwidth, 2)));
}

std::vector<Point> readPointsFromCSV(const std::string& fileName){
    std::vector<Point> points;
    std::ifstream data(fileName);
    std::string line;
    while (std::getline(data, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        std::vector<float> point;
        while (std::getline(lineStream, cell, ',')) {
            point.push_back(stod(cell));
        }
        points.emplace_back(Point(point));
    }
    return points;
}

void writeClustersToCSV(const std::string& fileName, const ClusterManager& clusterManager){
    std::ofstream outputFile(fileName);
    int clusterId = 0;
    for (auto &cluster : clusterManager.getClusters()) {
        for (auto &point : cluster.getOriginalPoints()) {
            for (int i = 0; i < point.getNumDimensions(); i++) {
                float value = point.getValues()[i];
                outputFile << value << ",";
            }
            outputFile << clusterId << "\n";
        }
        ++clusterId;
    }
}

void writeTimeToCSV(const std::string& fileName, int numThreads, float time, int numPoints, int dimensions, int numClusters, float bandwidth){
    if(std::experimental::filesystem::exists(fileName + ".csv")){
        std::ofstream outputFile(fileName + ".csv", std::ios_base::app);
        outputFile << numThreads << "," << time << "," << numPoints << "," << dimensions << "," << numClusters << "," << bandwidth << "\n";
    } else{
        std::ofstream outputFile(fileName + ".csv");
        outputFile << "Num threads" << "," << "Time" << "," << "Num points" << "," << "Dimensions" << "," << "Num clusters" << "," << "Bandwidth" << "\n";
        outputFile << numThreads << "," << time << "," << numPoints << "," << dimensions << "," << numClusters << "," << bandwidth << "\n";
    }
}
