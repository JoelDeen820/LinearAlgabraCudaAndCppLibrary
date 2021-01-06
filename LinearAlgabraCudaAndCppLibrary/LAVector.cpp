/* So some of the features that I have implemented
 *
 */

#include <new>
#include <iostream>
#include <exception>
#include <cmath>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "LAVector.h"
#include "LAVectorGPUOperations.cuh"
#include "LAVectorCPUOperations.h"


void Vector::copyintArray(int* values) {
	int* int_items = (int*)items;
	for (unsigned int i = 0; i < size; i++) {
		try {
			int_items[i] = values[i];
		}
		catch (std::exception& e) {
			std::cout << e.what();
			throw 1;
		}
	}
}

//void Vector::copyFloatArray(float* values) {
//	float* floatItems = (float*)items;
//	for (unsigned int i = 0; i < size; i++) {
//		try {
//			floatItems[i] = values[i];
//		}
//		catch (std::exception& e) {
//			std::cout << e.what();
//			throw 1;
//		}
//	}
//}
//
//void Vector::copyDoubleArray(double* values) {
//	double* doubleItems = (double*)items;
//	for (unsigned int i = 0; i < size; i++) {
//		try {
//			doubleItems[i] = values[i];
//		}
//		catch (const std::exception& e) {
//			std::cout << e.what();
//			throw 1;
//		}
//	}
//}

Vector::Vector(int* values, unsigned int incommingSize) {
	intialized = 1;
	size = incommingSize;
	items = new int[incommingSize];
	copyintArray(values);
	type = __INT;
}

//Vector::Vector(float* values, unsigned int incommingSize) {
//	intialized = 1;
//	size = incommingSize;
//	items = new float[incommingSize];
//	copyFloatArray(values);
//	type = __FLOAT;
//}
//
//Vector::Vector(double* values, unsigned int incommingSize) {
//	intialized = 1;
//	size = incommingSize;
//	items = new double[incommingSize];
//	copyDoubleArray(values);
//	type = __DOUBLE;
//}


Vector::~Vector() {
	delete[] items;
}

// Vector Addition Section ----------------------------------------------------------------

Vector* Vector::vectorAdd(Vector* otherVector) {
	int* resultList = nullptr;
	if (intialized == 0 || otherVector->intialized == 0) {
		return nullptr;
	}
	else if (size != otherVector->size) {
		return nullptr;
	}
	else {
		resultList = new int[size];
		if (size > MIN_GPU_ADDITION_ELEMENTS) {
			/*addWithCuda(resultList, (int*)items, (int *)otherVector->items, size);*/
			resultList = gpuIntAdd((int*)items, (int*)otherVector->items, size);
		}
		else if (size > MIN_GATEWAY_CPU_ADDITION_OPERATION_ELEMENTS) {
			resultList = multithreadedIntAdd((int*)items, (int*)otherVector->items, size);
		}
		else {
			resultList = singlethreadedIntAdd((int*)items, (int*)otherVector->items, size);
		}
	}

	Vector* new_vector = new Vector(resultList, size);
	delete[] resultList;
	return new_vector;
}

Vector* Vector::singleCPUAdd(Vector* otherVector) {
	int* resultList = nullptr;
	if (intialized == 0 || otherVector->intialized == 0) {
		return nullptr;
	}
	else if (size != otherVector->size) {
		return nullptr;
	}
	resultList = singlethreadedIntAdd((int*)items, (int*)otherVector->items, size);
	Vector* new_vector = new Vector(resultList, size);
	delete[] resultList;
	return new_vector;
}

// Vector Subtraction -------------------------------------------------------------------------

Vector* Vector::vectorSubtract(Vector* otherVector) {
	int* resultList = nullptr;
	if (intialized == 0 || otherVector->intialized == 0) {
		return nullptr;
	}
	else if (size != otherVector->size) {
		return nullptr;
	}
	else {
		resultList = new int[size];
		if (size > MIN_GPU_ADDITION_ELEMENTS) {
			resultList = gpuIntSubtract((int*)items, (int*)otherVector->items, size);
		}
		else if (size > MIN_GATEWAY_CPU_ADDITION_OPERATION_ELEMENTS) {
			resultList = multithreadedIntSubtract((int*)items, (int*)otherVector->items, size);
		}
		else {
			resultList = singlethreadedIntSubtract((int*)items, (int*)otherVector->items, size);
		}
	}

	Vector* new_vector = new Vector(resultList, size);
	delete[] resultList;
	return new_vector;
}

Vector* Vector::magnutudeMult(int value) {
	int* resultList = nullptr;
	if (intialized == 0) {
		return nullptr;
	}
	else if (size) {
		return nullptr;
	}
	else {
		resultList = new int[size];
		if (size > MIN_GPU_ADDITION_ELEMENTS) {
			//resultList = gpuIntSubtract((int*)items, value, size);
		}
		else if (size > MIN_GATEWAY_CPU_ADDITION_OPERATION_ELEMENTS) {
			resultList = multithreadedIntMultiply((int*)items, value, size);
		}
		else {
			resultList = singlethreadedIntMultiply((int*)items, value, size);
		}
	}
	Vector* new_vector = new Vector(resultList, size);
	delete[] resultList;
	return new_vector;
}

Vector* Vector::magnutudeDiv(int value) {
	int* resultList = nullptr;
	if (value == 0) {
		return nullptr;
	}
	if (intialized == 0) {
		return nullptr;
	}
	else if (size) {
		return nullptr;
	}
	else {
		resultList = new int[size];
		if (size > MIN_GPU_ADDITION_ELEMENTS) {
			//resultList = gpuIntSubtract((int*)items, value, size);
		}
		else if (size > MIN_GATEWAY_CPU_ADDITION_OPERATION_ELEMENTS) {
			resultList = multithreadedIntDivide((int*)items, value, size);
		}
		else {
			resultList = singlethreadedIntDivide((int*)items, value, size);
		}
	}
	Vector* new_vector = new Vector(resultList, size);
	delete[] resultList;
	return new_vector;
}

double Vector::getNorm1() {
	double sum = 0;
	double* double_values = (double*)items;
	for (unsigned int i = 0; i < size; i++) {
		sum += double_values[i];
	}
	return sum;
}

double Vector::getNorm2() {
	double sum = 0;
	double* double_values = (double*)items;
	for (unsigned int i = 0; i < size; i++) {
		sum += double_values[i] * double_values[i];
	}
	return sqrt(sum);
}

double Vector::getMagnitude() {
	return getNorm2();
}

unsigned int Vector::getSize() {
	return size;
}

unsigned char Vector::isInitalized() {
	return intialized;
}

void Vector::printItems() {
	std::cout << "{";
	int* intItems = (int*)items;
	for (unsigned int i = 0; i < size; i++) {
		std::cout << intItems[i] << ", ";
	}
	std::cout << "}\n";
}