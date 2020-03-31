/*
 ============================================================================
 Name        : MeanShiftClustering.cu
 Author      : Lorenzo Agnolucci
 Version     :
 Copyright   : 
 Description : CUDA implementation of Mean Shift clustering algorithm
 ============================================================================
 */

#include <iostream>
#include <numeric>
#include <stdlib.h>
#include <chrono>

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/sort.h>

#include "helper_math.h"
#include "Utils.h"

#define CUDA_CHECK_RETURN(value) CheckCudaErrorAux(__FILE__,__LINE__, #value, value)

#define BANDWIDTH 2
#define NUM_DIMENSIONS 3
#define NUM_ITERATIONS 10
#define NUM_TESTS 15
#define TILE_WIDTH 64
#define BLOCK_DIM TILE_WIDTH

__global__ void NaiveMeanShift(float* shiftedPoints, const float* __restrict__ originalPoints, const unsigned numPoints) {
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	float3 newPosition = make_float3(0.0, 0.0, 0.0);
	float totalWeight = 0.0;

	if(idx < numPoints){
		float x = shiftedPoints[idx];
		float y = shiftedPoints[idx + numPoints];
		float z = shiftedPoints[idx + 2 * numPoints];
		float3 shiftedPoint = make_float3(x, y, z);

		for(int i = 0; i < numPoints; i++){
			x = originalPoints[i];
			y = originalPoints[i + numPoints];
			z = originalPoints[i + 2 * numPoints];
			float3 originalPoint = make_float3(x, y, z);
			float3 difference = shiftedPoint - originalPoint;
			float squaredDistance = dot(difference, difference);
			float weight = std::exp((-squaredDistance) / (2 * powf(BANDWIDTH, 2)));
			newPosition += originalPoint * weight;
			totalWeight += weight;
		}
		newPosition /= totalWeight;
		shiftedPoints[idx] = newPosition.x;
		shiftedPoints[idx + numPoints] = newPosition.y;
		shiftedPoints[idx + 2 * numPoints] = newPosition.z;
	}
}

__global__ void TilingMeanShift(float* shiftedPoints, const float* __restrict__ originalPoints, const unsigned numPoints) {

	__shared__ float tile[TILE_WIDTH][3];

	int tx = threadIdx.x;
	int idx = blockIdx.x * blockDim.x + tx;

	float3 newPosition = make_float3(0.0, 0.0, 0.0);
	float totalWeight = 0.0;

	for (int tile_i = 0; tile_i < (numPoints - 1) / TILE_WIDTH + 1; ++tile_i) {

		int tile_idx = tile_i * TILE_WIDTH + tx;

		if(tile_idx < numPoints){
			tile[tx][0] = originalPoints[tile_idx];
			tile[tx][1] = originalPoints[tile_idx + numPoints];
			tile[tx][2] = originalPoints[tile_idx + 2 * numPoints];
		}else{
			tile[tx][0] = 0.0;
			tile[tx][1] = 0.0;
			tile[tx][2] = 0.0;
		}

		__syncthreads();

		if(idx < numPoints){
			float x = shiftedPoints[idx];
			float y = shiftedPoints[idx + numPoints];
			float z = shiftedPoints[idx + 2 * numPoints];
			float3 shiftedPoint = make_float3(x, y, z);

			for(int i = 0; i < TILE_WIDTH; i++){
				//if (tile[i][0] != 0.0 && tile[i][1] != 0.0 && tile[i][2] != 0.0) {
					float3 originalPoint = make_float3(tile[i][0], tile[i][1], tile[i][2]);
					float3 difference = shiftedPoint - originalPoint;
					float squaredDistance = dot(difference, difference);
					if(sqrt(squaredDistance) <= BANDWIDTH){
						float weight = std::exp((-squaredDistance) / (2 * powf(BANDWIDTH, 2)));
						newPosition += originalPoint * weight;
						totalWeight += weight;
					}
				//}
			}
		}
		__syncthreads();
	}

	if(idx < numPoints){
		newPosition /= totalWeight;
		shiftedPoints[idx] = newPosition.x;
		shiftedPoints[idx + numPoints] = newPosition.y;
		shiftedPoints[idx + 2 * numPoints] = newPosition.z;
	}

}

int main(void)
{

	std::string fileName = "dataset/3D_data_100000.csv";
	std::vector<float> inputPoints = readPointsFromCSV(fileName);

	int numPoints = inputPoints.size() / NUM_DIMENSIONS;
	printf("Num points %d\n", numPoints);

	float totalElapsedTime = 0.0;

	thrust::device_vector<float> originalPoints = inputPoints;
	thrust::device_vector<float> shiftedPoints = inputPoints;

	for(int j = 0; j < NUM_TESTS; j++){
		originalPoints = inputPoints;
		shiftedPoints = inputPoints;

		float* originalPointer = thrust::raw_pointer_cast(&originalPoints[0]);
		float* shiftedPointer = thrust::raw_pointer_cast(&shiftedPoints[0]);

		dim3 gridDim = dim3(ceil((float) numPoints / BLOCK_DIM));
		dim3 blockDim = dim3(BLOCK_DIM);

		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
		for(int i = 0; i < NUM_ITERATIONS; i++){
			TilingMeanShift<<<gridDim, blockDim>>> (shiftedPointer, originalPointer, numPoints);
			cudaDeviceSynchronize();
		}

		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
		float elapsedTime = std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();
		totalElapsedTime += elapsedTime;
	}
	totalElapsedTime /= NUM_TESTS;
	printf("\nTiling Mean Shift elapsed time: %f\n", totalElapsedTime);


	totalElapsedTime = 0.0;

	for(int j = 0; j < NUM_TESTS; j++){
			originalPoints = inputPoints;
			shiftedPoints = inputPoints;

			float* originalPointer = thrust::raw_pointer_cast(&originalPoints[0]);
			float* shiftedPointer = thrust::raw_pointer_cast(&shiftedPoints[0]);

			dim3 gridDim = dim3(ceil((float) numPoints / BLOCK_DIM));
			dim3 blockDim = dim3(BLOCK_DIM);

			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
			for(int i = 0; i < NUM_ITERATIONS; i++){
				NaiveMeanShift<<<gridDim, blockDim>>> (shiftedPointer, originalPointer, numPoints);
				cudaDeviceSynchronize();
			}

			std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
			float elapsedTime = std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();
			totalElapsedTime += elapsedTime;
	}
	totalElapsedTime /= NUM_TESTS;
	printf("\nNaive Mean Shift elapsed time: %f\n", totalElapsedTime);
/*

	thrust::host_vector<float> hostShiftedPoints = shiftedPoints;

	std::vector<float> outputPoints;
	std::vector<float> clusterPoints;



	outputPoints.resize(hostShiftedPoints.size());
	clusterPoints.resize(numPoints);
	thrust::copy(hostShiftedPoints.begin(), hostShiftedPoints.end(), outputPoints.begin());

	start = std::chrono::high_resolution_clock::now();

	std::vector<float3> clusters;

	float clusterEps = 5;

	for (int i = 0; i < numPoints; i++) {
		float x = hostShiftedPoints[i];
		float y = hostShiftedPoints[i + numPoints];
		float z = hostShiftedPoints[i + 2 * numPoints];
		float3 point = make_float3(x, y, z);
    	auto iter = clusters.begin();
        auto iterEnd = clusters.end();
        while(iter != iterEnd){
        	float3 difference = point - *iter;
        	float distance = sqrt(dot(difference, difference));
            if (distance <= clusterEps){
            	int clusterIndex =  iter - clusters.begin();
            	clusterPoints[i] = clusterIndex;
                break;
            }
            iter++;
        }
        if(iter == iterEnd){
            clusters.push_back(point);
            int clusterIndex = clusters.size() - 1;
            clusterPoints[i] = clusterIndex;
        }
    }

	end = std::chrono::high_resolution_clock::now();
	elapsedTime = std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();


	writeClustersToCSV("output.csv", inputPoints, clusterPoints, numPoints);

	printf("\nClustering elapsed time: %f", elapsedTime);
	printf("\nNum clusters: %lu", clusters.size());


*/
	return 0;
}
