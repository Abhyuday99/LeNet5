#include <iostream>
#include <cstdlib>

#include "functions.h"

using namespace std; 

float getConvolution(float *image , float *kernel ,int i ,int j,int n , int f ){
    float sum = 0.0;
     for(int x = 0;x< f;x++){
        for(int y = 0;y< f;y++){
            sum += *(image + (x + i)*n + (y + j))*(*(kernel + x*f + y)) ;
        }
     }
     
    return sum ;
}