#pragma once

#include "cuda_runtime.h"
#include "device_launch_parameters.h"


#define MIN_GPU_ADDITION_ELEMENTS 500
#define MAX_ADDING_THREADS 1024

// Visable User Functions ---------------------

int* gpuIntAdd(int*, int*, unsigned int);
int* gpuIntSubtract(int*, int*, unsigned int);
int* gpuIntMultiply(int*, int, unsigned int);
int* gpuIntDivide(int*, int, unsigned int);


// GPU Functions ------------------------------

__global__ void intAdd(int*, const int*, const int*, const unsigned int);
__global__ void intSubtract(int*, const int*, const int*, const unsigned int);
__global__ void intMultiply(int*, const int*, const int, const unsigned int);
__global__ void intDivide(int*, const int*, const int, const unsigned int);
__global__ void floatAdd(float*, float*, float*);
__global__ void floatSubtract(float*, float*, float*);
__global__ void floatMultiply(float*, float*, float*);
__global__ void floatDivide(float*, float*, float*);
__global__ void doubleAdd(double*, double*, double*);
__global__ void doubleSubtract(double*, double*, double*);
__global__ void doubleMultiply(double*, double*, double*);
__global__ void doubleDivide(double*, double*, double*);