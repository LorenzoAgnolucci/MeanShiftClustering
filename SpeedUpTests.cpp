//
// Created by lorenzo on 01/03/20.
//

#include "SpeedupTests.h"


void testDifferentSize(const std::string& inputPath, const std::string& outputPath){
    std::cout << "\nTesting different sizes" << std::endl;
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;

    std::string outputClustersFileName = outputPath + "different_size/";

    std::vector<std::string> fileNames;
    for (const auto & entry : std::experimental::filesystem::directory_iterator(inputPath))
        fileNames.emplace_back(entry.path().filename());
    std::sort(fileNames.begin(), fileNames.end());
    for (const auto & fileName : fileNames) {
        test(BANDWIDTH, inputPath + fileName, outputClustersFileName + "out_" + fileName, outputPath + "ResultsSpeedUpTests");
        std::cout << "" << std::endl;
    }
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;
    std::cout << "\n\n" << std::endl;
}

void testDifferentClusters(const std::string& inputPath, const std::string& outputPath){
    std::cout << "\nTesting different clusters" << std::endl;
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;

    std::string outputClustersFileName = outputPath + "different_clusters/";

    std::vector<std::string> fileNames;
    for (const auto & entry : std::experimental::filesystem::directory_iterator(inputPath))
        fileNames.emplace_back(entry.path().filename());
    std::sort(fileNames.begin(), fileNames.end());
    for (const auto & fileName : fileNames) {
        test(BANDWIDTH, inputPath + fileName, outputClustersFileName + "out_" + fileName, outputPath + "ResultsSpeedUpTests");
        std::cout << "" << std::endl;
    }
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;
    std::cout << "\n\n" << std::endl;
}

void testBandwidth(const std::string& inputPath, const std::string& outputPath){
    std::cout << "Testing different bandwidths" << std::endl;
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;

    std::string outputClustersFileName = outputPath + "bandwidth/";

    std::vector<std::string> fileNames;
    for (const auto & entry : std::experimental::filesystem::directory_iterator(inputPath))
        fileNames.emplace_back(entry.path().filename());
    std::sort(fileNames.begin(), fileNames.end());

    std::vector<float> bandwidths;
    bandwidths.push_back(1.0);
    bandwidths.push_back(2.0);
    bandwidths.push_back(5.0);
    bandwidths.push_back(10.0);

    for(const auto bandwidth: bandwidths) {
        for (const auto &fileName : fileNames) {
            test(bandwidth, inputPath + fileName, outputClustersFileName + "out_" + fileName,
                 outputPath + "ResultsSpeedUpTests");
            std::cout << "" << std::endl;
        }
    }
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;
    std::cout << "\n\n" << std::endl;
}

void test(float bandwidth, const std::string& inputFileName, const std::string& outputClustersFileName, const std::string& outputTimeFileName){
    std::vector<Point> points = readPointsFromCSV(inputFileName);

    for (int numThreads = 1; numThreads <= omp_get_max_threads(); numThreads++) {

        int numClusters = 0;
        float totalElapsedTime = 0;

        for (int k = 0; k < NUM_TEST_ITERATIONS; k++) {

            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

            std::vector<Point> shifted = meanShift(points, bandwidth, numThreads);

            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
            float elapsedTime = std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();

            ClusterManager clusterManager = ClusterManager(points, shifted, CLUSTER_EPS);
            clusterManager.buildClusters();
            numClusters = clusterManager.getNumClusters();
            writeClustersToCSV(outputClustersFileName, clusterManager);

            totalElapsedTime += elapsedTime;
        }
        std::cout << "Number of threads: " << numThreads << " || Time: " << totalElapsedTime / NUM_TEST_ITERATIONS
        << " || Number of points: " << points.size() << " || Dimensions: " << points[0].getNumDimensions()
        << " || Clusters: " << numClusters << " || Bandwidth: " << bandwidth << std::endl;
        writeTimeToCSV(outputTimeFileName, numThreads, totalElapsedTime / NUM_TEST_ITERATIONS, points.size(), points[0].getNumDimensions(), numClusters, bandwidth);
    }
}