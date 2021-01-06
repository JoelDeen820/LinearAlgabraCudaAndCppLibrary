#pragma once

#define MIN_CPU_OPERATIONS 10
#define MIN_GATEWAY_CPU_ADDITION_OPERATION_ELEMENTS (MIN_CPU_OPERATIONS * 5)

void addIntValues(int*, int*, int*, unsigned int, unsigned int);
void subtractIntValues(int*, int*, int*, unsigned int, unsigned int);
void multiplyIntValues(int*, int*, int, unsigned int, unsigned int);
void divideIntValues(int*, int*, int, unsigned int, unsigned int);

int* multithreadedIntAdd(int*, int*, unsigned int);
int* singlethreadedIntAdd(int*, int*, unsigned int);

int* multithreadedIntSubtract(int*, int*, unsigned int);
int* singlethreadedIntSubtract(int*, int*, unsigned int);

int* multithreadedIntMultiply(int*, int, unsigned int);
int* singlethreadedIntMultiply(int*, int, unsigned int);

int* multithreadedIntDivide(int*, int, unsigned int);
int* singlethreadedIntDivide(int*, int, unsigned int);