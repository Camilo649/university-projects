#include <stdio.h> // printf
#include <stdlib.h> // calloc
#include <assert.h> // assert
#include <cuda.h> // CUDA library
#include "helper_cuda.h" // CUDA error checking

// integer ceiling division
#define DIV_CEIL(a,b) (((a)+(b)-1)/(b))
// minimum
#define MIN(a,b) (((a)<(b))?(a):(b))

#define BLOCK_SIZE 128
#define NUM_WARPS (BLOCK_SIZE/CUDA_WARP_SIZE)

__global__ void set(const uint N, int * const values) {
	int gtid = blockIdx.x*blockDim.x + threadIdx.x;
	if (gtid<N)
		values[gtid] = (int) warpSize*(1+cosf((float)gtid));
}

__global__ void warp_scan3(const int * const values, int * const inclusive, int * const exclusive) {
	int tid = threadIdx.x;
	int lane = tid % warpSize;
	int gtid = blockIdx.x * blockDim.x + threadIdx.x;

	// read from global
	int x = values[gtid];

	int sum = x;
	int n=0;
	#define FULL_MASK 0xffffffff
	n = __shfl_up_sync(FULL_MASK, sum, 1);
	if (lane >= 1) sum += n;
	__syncwarp();
	n = __shfl_up_sync(FULL_MASK, sum, 2);
	if (lane >= 2) sum += n;
	__syncwarp();
	n = __shfl_up_sync(FULL_MASK, sum, 4);
	if (lane >= 4) sum += n;
	__syncwarp();
	n = __shfl_up_sync(FULL_MASK, sum, 8);
	if (lane >= 8) sum += n;
	__syncwarp();
	n = __shfl_up_sync(FULL_MASK, sum, 16);
	if (lane >= 16) sum += n;
	__syncwarp();

	/*
	//Versión más cortita y de igual desempeño
	#pragma unroll
	for (int i=1; i<warpSize; i*=2) {
		int n = __shfl_up(FULL_MASK, sum, i);
		if (lane >= i) sum += n;
		__syncwarp();
	}
	*/
	

	inclusive[gtid] = sum;
	exclusive[gtid] = sum - x;
}



int main(int argc, char **argv)
{
	int *d_values = NULL, *h_values = NULL; // pointers in Host and Device
	int *d_inclusive = NULL, *h_inclusive = NULL;
	int *d_exclusive = NULL, *h_exclusive = NULL;
	assert(2 == argc);
	const unsigned int N = 1<<(atoi(argv[1])); // vector size
	assert(0 == N%32); // múltiplo de warp

	checkCudaErrors(cudaMalloc(&d_values, N * sizeof(int)));
	checkCudaErrors(cudaMalloc(&d_inclusive, N * sizeof(int)));
	checkCudaErrors(cudaMalloc(&d_exclusive, N * sizeof(int)));
	checkCudaErrors(cudaMallocHost(&h_values, N * sizeof(int)));
	checkCudaErrors(cudaMallocHost(&h_inclusive, N * sizeof(int)));
	checkCudaErrors(cudaMallocHost(&h_exclusive, N * sizeof(int)));
	assert(d_values && h_values && d_inclusive && h_inclusive && d_exclusive && h_exclusive);

	dim3 block_size(BLOCK_SIZE);
	dim3 grid_size(DIV_CEIL(N,BLOCK_SIZE));
	set<<<grid_size, block_size>>>(N, d_values);
	getLastCudaError("set kernel failed");
	warp_scan3<<<grid_size, block_size>>>((const int*)d_values, d_inclusive, d_exclusive);
	getLastCudaError("warp_scan3 kernel failed");
	cudaDeviceSynchronize();

	checkCudaErrors(cudaMemcpy(h_values, d_values, N*sizeof(int), cudaMemcpyDefault));
	checkCudaErrors(cudaMemcpy(h_inclusive, d_inclusive, N*sizeof(int), cudaMemcpyDefault));
	checkCudaErrors(cudaMemcpy(h_exclusive, d_exclusive, N*sizeof(int), cudaMemcpyDefault));
	unsigned int i=0;
	unsigned int lane=0;
	for (i=0; i<N; i+=CUDA_WARP_SIZE) {
		int inclusive = 0, exclusive = 0;
		for (lane=0; lane<CUDA_WARP_SIZE; ++lane) {
			inclusive += h_values[i+lane];
			if (inclusive!=h_inclusive[i+lane] || exclusive!=h_exclusive[i+lane]) {
				goto EXIT; // "Go To Statement Considered Harmful"
			}
			exclusive += h_values[i+lane];
		}
	}
EXIT:
	if (N != i) { // if error, print complete lane.
		printf("Error in warp %d, lane %d\n", i/CUDA_WARP_SIZE, lane);
		for (unsigned int lane=0; lane<CUDA_WARP_SIZE; ++lane) {
			printf("%d ", h_values[i+lane]);
		} printf("\n");
		for (unsigned int lane=0; lane<CUDA_WARP_SIZE; ++lane) {
			printf("%d ", h_inclusive[i+lane]);
		} printf("\n");
		for (unsigned int lane=0; lane<CUDA_WARP_SIZE; ++lane) {
			printf("%d ", h_exclusive[i+lane]);
		} printf("\n");
	}

	checkCudaErrors(cudaFreeHost(h_values));
	checkCudaErrors(cudaFreeHost(h_inclusive));
	checkCudaErrors(cudaFreeHost(h_exclusive));
	checkCudaErrors(cudaFree(d_values));
	checkCudaErrors(cudaFree(d_inclusive));
	checkCudaErrors(cudaFree(d_exclusive));

	return 0;
}
