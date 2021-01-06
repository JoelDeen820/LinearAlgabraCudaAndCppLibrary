#include <iostream>


#include "LAVector.h"


#define SIZE 100000


int main(int argc, char** argv) {
	int* values = new int[SIZE];
	for (int i = 0; i < SIZE; i++) {
		values[i] = 1;
	}
	Vector* vec1 = new Vector(values, SIZE);
	//vec1->printItems();
	Vector* vec2 = new Vector(values, SIZE);
	std::cout << "Starting GPU Compute";
	Vector* results_GPU = vec1->vectorAdd(vec2);
	std::cout << "Starting Single Threaded CPU Compute";
	Vector* results_SCPU = vec1->singleCPUAdd(vec2);
	delete vec1;
	delete vec2;
	delete results_GPU;
	delete results_SCPU;
	delete[] values;
	return 0;
}