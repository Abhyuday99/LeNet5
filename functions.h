#include <string>
float getConvolution(float *image , float *kernel ,int i ,int j,int n , int f);
float* getMatrix(std::string);
float* invertKernel(float* input, int n);
float* applyPadding(float* image,int p,int n);
float* Transformkernel(float* kernel, int n, int f);
float* TransformImage(float* image,int n , int k);
float getConvolution_matrixmult(float *image,float *matrix,int i,int j,int n,int f);
float* relu(float* arr,int n);
float* tanh(float* arr,int n);
float max_pool(float *arr, int n, int f, int s, int i, int j);
float avg_pool(float *arr, int n, int f, int s, int i, int j);
float sigmoid(float f);
float softmax(float f, float sum);
float* MKL_matrixmult(int d, int k, float *arr, float* kernel, float* processed);
float* OpenBLAS_matrixmult(int d, int k, float *arr, float* kernel, float* processed);
void* PTHConvolution_matrixmult(void* ptr);
float* pThread_matrixmult(float* A,float* B,int x,int y);
