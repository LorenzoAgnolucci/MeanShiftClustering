/*
 * Utils.h
 *
 *  Created on: 13/mar/2020
 *      Author: lorenzo
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<float> readPointsFromCSV(const std::string& fileName);

void writeClustersToCSV(const std::string& fileName, const std::vector<float> originalPoints, const std::vector<float> clusterPoints, const int numPoints);

#endif /* UTILS_H_ */
