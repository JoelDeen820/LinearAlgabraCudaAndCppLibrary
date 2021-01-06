#include <new>
#include <windows.h>
#include <thread>
#include <vector>
#include <iostream>

#include "LAVectorCPUOperations.h"

// -- Multithreading Funcions --------------------------------------------------------------------------------

void addIntValues(int* destination, int* value1, int* value2, unsigned int start, unsigned int end) {
	for (unsigned int i = start; i < end; i++) {
		destination[i] = value1[i] + value2[i];
	}
}

void subtractIntValues(int* destination, int* value1, int* value2, unsigned int start, unsigned int end) {
	for (unsigned int i = start; i < end; i++) {
		destination[i] = value1[i] + value2[i];
	}
}

void multiplyIntValues(int* destination, int* vector, int value, unsigned int start, unsigned int end) {
	for (unsigned int i = start; i < end; i++) {
		destination[i] = vector[i] * value;
	}
}

void divideIntValues(int* destination, int* values, int value, unsigned int start, unsigned int end) {
	for (unsigned int i = start; i < end; i++) {
		destination[i] = values[i] * value;
	}
}

// -- addition operations -------------------------------------------------------------------------------------
int* multithreadedIntAdd(int* values1, int* values2, unsigned int size) {
	int* result = new int[size];
	unsigned int nthreads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads;
	unsigned int values_left = size;
	unsigned int ending_value;
	unsigned int interval_size;
	if (size < nthreads * MIN_CPU_OPERATIONS) {
		ending_value = size - MIN_CPU_OPERATIONS;
		for (; ending_value >= MIN_CPU_OPERATIONS; ending_value -= MIN_CPU_OPERATIONS) {
			threads.push_back(std::thread(addIntValues, result, values1, values2, ending_value, values_left));
			values_left -= MIN_CPU_OPERATIONS;
		}
		addIntValues(result, values1, values2, 0, values_left);
		for (auto& thread : threads) {
			thread.join();
		}
	}
	else {
		interval_size = size / nthreads;
		ending_value = size - interval_size;
		for (unsigned int i = 1; i < nthreads; i++) {
			threads.push_back(std::thread(addIntValues, result, values1, values2, ending_value, values_left));
			values_left -= interval_size;
			ending_value -= interval_size;
		}
		addIntValues(result, values1, values2, 0, values_left);
		for (auto& thread : threads) {
			thread.join();
		}
	}
	return result;
}

int* singlethreadedIntAdd(int* values1, int* values2, unsigned int size) {
	int* result = new int[size];
	for (unsigned int i = 0; i < size; i++) {
		result[i] = values1[i] + values2[i];
	}
	return result;
}

// -- Subtraction Operations --------------------------------------------------------------------------------------

int* multithreadedIntSubtract(int* values1, int* values2, unsigned int size) {
	int* result = new int[size];
	unsigned int nthreads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads;
	unsigned int values_left = size;
	unsigned int ending_value;
	unsigned int interval_size;
	if (size < nthreads * MIN_CPU_OPERATIONS) {
		ending_value = size - MIN_CPU_OPERATIONS;
		for (; ending_value >= MIN_CPU_OPERATIONS; ending_value -= MIN_CPU_OPERATIONS) {
			threads.push_back(std::thread(subtractIntValues, result, values1, values2, ending_value, values_left));
			values_left -= MIN_CPU_OPERATIONS;
		}
		subtractIntValues(result, values1, values2, 0, values_left);
		for (auto& thread : threads) {
			thread.join();
		}
	}
	else {
		interval_size = size / nthreads;
		ending_value = size - interval_size;
		for (unsigned int i = 1; i < nthreads; i++) {
			threads.push_back(std::thread(subtractIntValues, result, values1, values2, ending_value, values_left));
			values_left -= interval_size;
			ending_value -= interval_size;
		}
		subtractIntValues(result, values1, values2, 0, values_left);
		for (auto& thread : threads) {
			thread.join();
		}
	}
	return result;
}

int* singlethreadedIntSubtract(int* values1, int* values2, unsigned int size) {
	int* result = new int[size];
	for (unsigned int i = 0; i < size; i++) {
		result[i] = values1[i] - values2[i];
	}
	return result;
}

// -- Multiplication Operations -----------------------------------------------------------------------------------

int* multithreadedIntMultiply(int* values1, int value, unsigned int size) {
	int* result = new int[size];
	unsigned int nthreads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads;
	unsigned int values_left = size;
	unsigned int ending_value;
	unsigned int interval_size;
	if (size < nthreads * MIN_CPU_OPERATIONS) {
		ending_value = size - MIN_CPU_OPERATIONS;
		for (; ending_value >= MIN_CPU_OPERATIONS; ending_value -= MIN_CPU_OPERATIONS) {
			threads.push_back(std::thread(multiplyIntValues, result, values1, value, ending_value, values_left));
			values_left -= MIN_CPU_OPERATIONS;
		}
		multiplyIntValues(result, values1, value, 0, values_left);
		for (auto& thread : threads) {
			thread.join();
		}
	}
	else {
		interval_size = size / nthreads;
		ending_value = size - interval_size;
		for (unsigned int i = 1; i < nthreads; i++) {
			threads.push_back(std::thread(multiplyIntValues, result, values1, value, ending_value, values_left));
			values_left -= interval_size;
			ending_value -= interval_size;
		}
		multiplyIntValues(result, values1, value, 0, values_left);
		for (auto& thread : threads) {
			thread.join();
		}
	}
	return result;
}

int* singlethreadedIntMultiply(int* values, int value, unsigned int size) {
	int* result = new int[size];
	for (unsigned int i = 0; i < size; i++) {
		result[i] = values[i] * value;
	}
	return result;
}

// -- Divide Operations ---------------------------------------------------------------------------------------

int* multithreadedIntDivide(int* values, int value, unsigned int size) {
	if (value == 0) {
		return nullptr;
	}
	int* result = new int[size];
	unsigned int nthreads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads;
	unsigned int values_left = size;
	unsigned int ending_value;
	unsigned int interval_size;
	if (size < nthreads * MIN_CPU_OPERATIONS) {
		ending_value = size - MIN_CPU_OPERATIONS;
		for (; ending_value >= MIN_CPU_OPERATIONS; ending_value -= MIN_CPU_OPERATIONS) {
			threads.push_back(std::thread(divideIntValues, result, values, value, ending_value, values_left));
			values_left -= MIN_CPU_OPERATIONS;
		}
		divideIntValues(result, values, value, 0, values_left);
		for (auto& thread : threads) {
			thread.join();
		}
	}
	else {
		interval_size = size / nthreads;
		ending_value = size - interval_size;
		for (unsigned int i = 1; i < nthreads; i++) {
			threads.push_back(std::thread(divideIntValues, result, values, value, ending_value, values_left));
			values_left -= interval_size;
			ending_value -= interval_size;
		}
		divideIntValues(result, values, value, 0, values_left);
		for (auto& thread : threads) {
			thread.join();
		}
	}
	return result;
}

int* singlethreadedIntDivide(int* values, int value, unsigned int size) {
	if (value == 0) {
		return nullptr;
	}
	int* result = new int[size];
	for (unsigned int i = 0; i < size; i++) {
		result[i] = values[i] / value;
	}
	return result;
}