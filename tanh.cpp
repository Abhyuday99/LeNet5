#include <iostream>
#include <math.h>

#include "functions.h"

using namespace std;

float* tanh(float* arr,int n){

    float* output = (float*) malloc(sizeof(float)*n*n);
    float* temp = arr;
    float entry,result;
    for(int i = 0;i< n;i++){
        for(int j = 0;j< n;j++){
            entry = *(temp + i*n + j);
            result = exp(2*entry);
            *(output + i*n + j) = (result-1)/(result + 1);
        }
    }

    return output;
}