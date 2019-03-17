#include <cblas.h>
#include <iostream>
#include <cstdlib>
#include<ctime>

using namespace std ;

float* OpenBLAS_matrixmult(int d, int k, float *arr, float* kernel, float* processed) {

	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, d*d,1,k*k, 1.0, arr, k*k, kernel, 1, 0.0, processed, 1);
	return processed;
}
