/* Author: Joel Deen
* This library takes in arrays of intergers and preforms various vector operations using the GPU.
*/


#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "LAVectorGPUOperations.cuh"
#include <exception>

// GPU kernel Calls ----------------------------------------------------------------------------------------------------------

// just the int add kernal, nothing special for any of the kernals
__global__ void intAdd(int* c, const int* a, const int* b, const unsigned int d)
{
	int i = threadIdx.x + blockIdx.x * blockDim.x;
	if (i < d) {
		c[i] = a[i] + b[i];
	}
}

__global__ void intSubtract(int* c, const int* a, const int* b, const unsigned int d) {
	int i = threadIdx.x + blockIdx.x * blockDim.x;
	if (i < d) {
		c[i] = a[i] + b[i];
	}
}

__global__ void intMultiply(int* result, const int* val1, const int val2, const unsigned int size) {
	int i = threadIdx.x + blockIdx.x * blockDim.x;
	if (i < size) {
		result[blockIdx.x] = val1[blockIdx.x] * val2;
	}
}

__global__ void intDivide(int* result, const int* val1, const int val2, const unsigned int size) { // we are assuming that the user does some prechecking for zero
	int i = threadIdx.x + blockIdx.x * blockDim.x;
	if (i < size) {
		result[blockIdx.x] = val1[blockIdx.x] / val2;
	}
}

// CPU Calls -----------------------------------------------------------------------------------------------------------------

int* gpuIntAdd(int* values1, int* values2, unsigned int size) {
	cudaError_t cuda_status = cudaSetDevice(0);
	if (cuda_status != cudaSuccess) {
		throw 1;
	}
	int* result = new int[size];
	int* cuda_vec1;
	int* cuda_vec2;
	int* cuda_result;

	cuda_status = cudaMalloc((void**)&cuda_vec1, size * sizeof(int));
	if (cuda_status != cudaSuccess) {
		throw 2;
	}
	cuda_status = cudaMalloc((void**)&cuda_vec2, size * sizeof(int));
	if (cuda_status != cudaSuccess) {
		throw 2;
	}
	cuda_status = cudaMalloc((void**)&cuda_result, size * sizeof(int));
	if (cuda_status != cudaSuccess) {
		throw 2;
	}

	cuda_status = cudaMemcpy(cuda_vec1, values1, size * sizeof(int), cudaMemcpyHostToDevice);
	if (cuda_status != cudaSuccess) {
		throw 3;
	}
	cuda_status = cudaMemcpy(cuda_vec2, values2, size * sizeof(int), cudaMemcpyHostToDevice);
	if (cuda_status != cudaSuccess) {
		throw 3;
	}
	intAdd << <1 + (size / MAX_ADDING_THREADS), MAX_ADDING_THREADS >> > (cuda_result, cuda_vec1, cuda_vec2, size);

	cuda_status = cudaGetLastError();
	if (cuda_status != cudaSuccess) {
		throw 4;
	}

	cuda_status = cudaMemcpy(result, cuda_result, size * sizeof(int), cudaMemcpyDeviceToHost);
	if (cuda_status != cudaSuccess) {
		throw 5;
	}

	cuda_status = cudaFree(cuda_vec1);
	if (cuda_status != cudaSuccess) {
		throw 6;
	}
	cuda_status = cudaFree(cuda_vec2);
	if (cuda_status != cudaSuccess) {
		throw 6;
	}
	cuda_status = cudaFree(cuda_result);
	if (cuda_status != cudaSuccess) {
		throw 6;
	}

	return result;
}

int* gpuIntSubtract(int* values1, int* values2, unsigned int size) {
	cudaError_t cuda_status = cudaSetDevice(0);
	if (cuda_status != cudaSuccess) {
		throw 1;
	}
	int* result = new int[size];
	int* cuda_vec1;
	int* cuda_vec2;
	int* cuda_result;

	cuda_status = cudaMalloc((void**)&cuda_vec1, size * sizeof(int));
	if (cuda_status != cudaSuccess) {
		throw 2;
	}
	cuda_status = cudaMalloc((void**)&cuda_vec2, size * sizeof(int));
	if (cuda_status != cudaSuccess) {
		throw 2;
	}
	cuda_status = cudaMalloc((void**)&cuda_result, size * sizeof(int));
	if (cuda_status != cudaSuccess) {
		throw 2;
	}

	cuda_status = cudaMemcpy(cuda_vec1, values1, size * sizeof(int), cudaMemcpyHostToDevice);
	if (cuda_status != cudaSuccess) {
		throw 3;
	}
	cuda_status = cudaMemcpy(cuda_vec2, values2, size * sizeof(int), cudaMemcpyHostToDevice);
	if (cuda_status != cudaSuccess) {
		throw 3;
	}
	intSubtract << <1 + (size / MAX_ADDING_THREADS), MAX_ADDING_THREADS >> > (cuda_result, cuda_vec1, cuda_vec2, size);
	cuda_status = cudaGetLastError();
	if (cuda_status != cudaSuccess) {
		throw 4;
	}

	cuda_status = cudaMemcpy(result, cuda_result, size * sizeof(int), cudaMemcpyDeviceToHost);
	if (cuda_status != cudaSuccess) {
		throw 5;
	}

	cuda_status = cudaFree(cuda_vec1);
	if (cuda_status != cudaSuccess) {
		throw 6;
	}
	cuda_status = cudaFree(cuda_vec2);
	if (cuda_status != cudaSuccess) {
		throw 6;
	}
	cuda_status = cudaFree(cuda_result);
	if (cuda_status != cudaSuccess) {
		throw 6;
	}

	return result;
}

int* gpuIntMultiply(int* values1, int value, unsigned int size) {
	cudaError_t cuda_status = cudaSetDevice(0);
	if (cuda_status != cudaSuccess) {
		throw 1;
	}
	int* result = new int[size];
	int* cuda_vec1;
	int* cuda_result;

	cuda_status = cudaMalloc((void**)&cuda_vec1, size * sizeof(int));
	if (cuda_status != cudaSuccess) {
		throw 2;
	}
	cuda_status = cudaMalloc((void**)&cuda_result, size * sizeof(int));
	if (cuda_status != cudaSuccess) {
		throw 2;
	}

	cuda_status = cudaMemcpy(cuda_vec1, values1, size * sizeof(int), cudaMemcpyHostToDevice);
	if (cuda_status != cudaSuccess) {
		throw 3;
	}
	intMultiply << <1 + (size / MAX_ADDING_THREADS), MAX_ADDING_THREADS >> > (cuda_result, cuda_vec1, value, size);
	cuda_status = cudaGetLastError();
	if (cuda_status != cudaSuccess) {
		throw 4;
	}

	cuda_status = cudaMemcpy(result, cuda_result, size * sizeof(int), cudaMemcpyDeviceToHost);
	if (cuda_status != cudaSuccess) {
		throw 5;
	}

	cuda_status = cudaFree(cuda_vec1);
	if (cuda_status != cudaSuccess) {
		throw 6;
	}
	cuda_status = cudaFree(cuda_result);
	if (cuda_status != cudaSuccess) {
		throw 6;
	}

	return result;
}

int* gpuIntDivide(int* values1, int value, unsigned int size) {
	if (value == 0) {
		throw 7;
	}
	cudaError_t cuda_status = cudaSetDevice(0);
	if (cuda_status != cudaSuccess) {
		throw 1;
	}
	int* result = new int[size];
	int* cuda_vec1;
	int* cuda_result;

	cuda_status = cudaMalloc((void**)&cuda_vec1, size * sizeof(int));
	if (cuda_status != cudaSuccess) {
		throw 2;
	}
	cuda_status = cudaMalloc((void**)&cuda_result, size * sizeof(int));
	if (cuda_status != cudaSuccess) {
		throw 2;
	}

	cuda_status = cudaMemcpy(cuda_vec1, values1, size * sizeof(int), cudaMemcpyHostToDevice);
	if (cuda_status != cudaSuccess) {
		throw 3;
	}
	intMultiply << <1 + (size / MAX_ADDING_THREADS), MAX_ADDING_THREADS >> > (cuda_result, cuda_vec1, value, size);
	cuda_status = cudaGetLastError();
	if (cuda_status != cudaSuccess) {
		throw 4;
	}

	cuda_status = cudaMemcpy(result, cuda_result, size * sizeof(int), cudaMemcpyDeviceToHost);
	if (cuda_status != cudaSuccess) {
		throw 5;
	}

	cuda_status = cudaFree(cuda_vec1);
	if (cuda_status != cudaSuccess) {
		throw 6;
	}
	cuda_status = cudaFree(cuda_result);
	if (cuda_status != cudaSuccess) {
		throw 6;
	}

	return result;
}