#include <iostream>

#include "functions.h"

using namespace std;

float* relu(float* arr,int n){

    float* output = (float*) malloc(sizeof(float)*n*n) ;
    float* temp = arr ;
    float entry ;
    for(int i = 0 ; i < n ; i++){

        for(int j = 0 ; j < n ; j++){
            entry = *(temp + i*n + j);
           if(entry > 0){
                *(output + i*n + j) = entry ;
           }
           else{
                *(output + i*n + j) = 0 ;
           }
        }
    }
    
    return output ;
}