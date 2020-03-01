#include <iostream>
#include <experimental/filesystem>

#include "SpeedupTests.h"


int main() {

    std::string inputPath = "../datasets/";
    std::string outputPath = "../output/";

    if(std::experimental::filesystem::exists(outputPath + "ResultsSpeedUpTests.csv")){
        std::experimental::filesystem::remove(outputPath + "ResultsSpeedUpTests.csv");
    }

    testDifferentSize(inputPath + "different_size/", outputPath);
    testDifferentClusters(inputPath + "different_clusters/", outputPath);
    testBandwidth(inputPath + "bandwidth/", outputPath);

    return 0;
}
