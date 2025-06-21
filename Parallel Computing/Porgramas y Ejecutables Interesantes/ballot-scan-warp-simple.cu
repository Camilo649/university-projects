

//************************************
// TODO, no anda
//************************************

#include <stdio.h> // printf
#include <stdlib.h> // calloc
#include <assert.h> // assert
#include <cuda.h> // CUDA library
#include "helper_cuda.h" // CUDA error checking

// integer ceiling division
#define DIV_CEIL(a,b) (((a)+(b)-1)/(b))
// maximum
#define MIN(a,b) (((a)<(b))?(a):(b))

#define BLOCK_SIZE 32
#define NUM_WARPS (BLOCK_SIZE/CUDA_WARP_SIZE)

__global__ void set(const uint N, int * const values) {
	int gtid = blockIdx.x*blockDim.x + threadIdx.x;
	if (gtid<N)
		values[gtid] = (int) warpSize*(1+cosf((float)gtid));
}

__device__ __forceinline__ uint bfi(uint x, uint y, uint bit, uint numBits) {
	uint ret;
	asm("bfi.b32 %0, %1, %2, %3, %4;" :
		"=r"(ret) : "r"(y), "r"(x), "r"(bit), "r"(numBits));
	return ret;
}

__global__ void ballotScanWarp(const int * const dataIn_global, int * const dataOut_global, uint * const countOut_global) {
	uint tid  = threadIdx.x;
	uint gtid = blockIdx.x*blockDim.x + threadIdx.x;

	int val = dataIn_global[gtid];

	uint flag = (42<=val);

	#define FULL_MASK 0xffffffff
	uint bits = __ballot_sync(FULL_MASK, flag);

	uint mask = bfi(0, FULL_MASK, 0, tid);
	uint exc = __popc(mask & bits);
	uint total = __popc(bits);

	dataOut_global[gtid] = exc;

	*countOut_global = total;
}


int main(int argc, char **argv)
{
	int *d_values = NULL, *h_values = NULL; // pointers in Host and Device
	int *d_inclusive = NULL, *h_inclusive = NULL;
	uint *d_count = NULL, *h_count = NULL;
	assert(2 == argc);
	const unsigned int N = (1<<atoi(argv[1])); // vector size
	assert(0 == N%CUDA_WARP_SIZE);

	checkCudaErrors(cudaMalloc(&d_values, N * sizeof(int)));
	checkCudaErrors(cudaMalloc(&d_inclusive, N * sizeof(int)));
	checkCudaErrors(cudaMalloc(&d_count, 1 * sizeof(uint)));
	checkCudaErrors(cudaMallocHost(&h_values, N * sizeof(int)));
	checkCudaErrors(cudaMallocHost(&h_inclusive, N * sizeof(int)));
	checkCudaErrors(cudaMallocHost(&h_count, 1 * sizeof(uint)));
	assert(d_values && h_values && d_inclusive && h_inclusive && d_count && h_count);

	dim3 block_size(BLOCK_SIZE);
	dim3 grid_size(DIV_CEIL(N,BLOCK_SIZE));
	set<<<grid_size, block_size>>>(N, d_values);
	getLastCudaError("set kernel failed");
	ballotScanWarp<<<grid_size, block_size>>>(d_values, d_inclusive, d_count);
	getLastCudaError("ballotScanWarp kernel failed");
	checkCudaErrors(cudaDeviceSynchronize());

	checkCudaErrors(cudaMemcpy(h_values, d_values, N*sizeof(int), cudaMemcpyDefault));
	checkCudaErrors(cudaMemcpy(h_count, d_count, 1*sizeof(int), cudaMemcpyDefault));
	checkCudaErrors(cudaMemcpy(h_inclusive, d_inclusive, (*h_count)*sizeof(int), cudaMemcpyDefault));
	unsigned int i=0;
	// First warp
	printf("%d\n", *h_count);
	for (i=0; i<CUDA_WARP_SIZE; ++i)
		printf("%2d ", h_values[i]);
	printf("\n");
	for (i=0; i<*h_count; ++i)
		printf("%2d ", h_inclusive[i]);
	printf("\n");

	checkCudaErrors(cudaFreeHost(h_values));
	checkCudaErrors(cudaFreeHost(h_inclusive));
	checkCudaErrors(cudaFreeHost(h_count));
	checkCudaErrors(cudaFree(d_values));
	checkCudaErrors(cudaFree(d_inclusive));
	checkCudaErrors(cudaFree(d_count));

	return 0;
}
