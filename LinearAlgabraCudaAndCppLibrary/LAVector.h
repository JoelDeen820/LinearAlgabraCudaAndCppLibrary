#pragma once
#define __INT 0
#define __FLOAT 1
#define __DOUBLE 2
// #define __USRDEF 3
#define __UINT 3
#define __UFLOAT 5
#define __UDOUBLE 6

class Vector
{
private:
	unsigned char intialized; // Not going to be used as a character, more as a number
	unsigned int size;
	void* items;
	unsigned int type; // 0 = int, 1 = float, 2 = double, 3 = unsigned int, 4 = unsigned float, 5 = unsigned double, 6 both
//	int (*add)(void*, void*);
//	int (*subtract)(void*, void*);
//	int (*multiply)(void*, void*);
//	int (*divide)(void*, void*);
//	int (*copy)(void**, void*);
	void copyintArray(int*);
	/*void copyFloatArray(float*);
	void copyDoubleArray(double*);*/
public:
	Vector(int*, unsigned int);
	~Vector();
	Vector* vectorAdd(Vector*);
	Vector* singleCPUAdd(Vector*);
	Vector* vectorSubtract(Vector*);
	Vector* magnutudeMult(int);
	Vector* magnutudeDiv(int);
	double getNorm1();
	double getNorm2();
	double getMagnitude();
	unsigned int getSize();
	/*Vector(float*, unsigned int);
	Vector(double*, unsigned int);
	Vector(void*, int, int (*)(void*, void*), int (*)(void*, void*), int (*)(void*, void*), int (*)(void*, void*));
	Vector(Vector* otherVector);*/
	/*int magnutudeMult(float);
	int magnutudeMult(double);*/
	/*int magnutudeDiv(float);
	int magnutudeDiv(double);*/
	//	void freeVec();
	unsigned char isInitalized();
	void printItems();

};

