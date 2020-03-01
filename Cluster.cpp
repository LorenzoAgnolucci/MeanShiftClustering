//
// Created by lorenzo on 27/12/19.
//

#include "Cluster.h"


void Cluster::computeCentroid(){
    std::vector<float> averagedCoordinates = std::vector<float>(this->centroid.getNumDimensions(), 0);
    for(const auto& point: shiftedPoints){
        for(int i = 0; i < point.getNumDimensions(); i++){
            averagedCoordinates[i] += point.getValues()[i];
        }
    }
    for(auto& value: averagedCoordinates){
        value /= shiftedPoints.size();
    }
    this->centroid = Point(averagedCoordinates);
}