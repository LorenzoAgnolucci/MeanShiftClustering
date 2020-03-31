/*
 * Utils.cpp
 *
 *  Created on: 13/mar/2020
 *      Author: lorenzo
 */

#include "Utils.h"

std::vector<float> readPointsFromCSV(const std::string& fileName){
    std::vector<float> x;
    std::vector<float> y;
    std::vector<float> z;
    std::ifstream data(fileName);
    std::string line;
    while(std::getline(data, line)){
    	std::vector<float> point;
        std::stringstream lineStream(line);
        std::string cell;
        while(std::getline(lineStream, cell, ',')){
            point.push_back(stod(cell));
        }
        x.push_back(point[0]);
        y.push_back(point[1]);
        z.push_back(point[2]);
    }
    std::vector<float> points = x;
    points.insert(points.end(), y.begin(), y.end());
    points.insert(points.end(), z.begin(), z.end());
    return points;
}

void writeClustersToCSV(const std::string& fileName, const std::vector<float> originalPoints, const std::vector<float> clusterPoints, const int numPoints){
	std::ofstream outputFile(fileName);
	for (int i = 0; i < numPoints; i++) {
		outputFile << originalPoints[i] << ",";
		outputFile << originalPoints[i + numPoints] << ",";
		outputFile << originalPoints[i + 2 * numPoints] << ",";
		outputFile << clusterPoints[i] << "\n";
	}
}
