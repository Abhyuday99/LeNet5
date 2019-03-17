#include <iostream>
#include <cstdlib>

#include "functions.h"

using namespace std; 

float* invertKernel(float* kernel,int f){
    float* arr = (float*)malloc(sizeof(float)*f*f);
    float* temp = arr;
    kernel += f*f - 1;
    for(int i=0;i<f*f;i++){
        *arr = *(kernel);
        arr++;
        kernel--;
    }
    
    return temp;
}