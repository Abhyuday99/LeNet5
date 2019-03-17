//#include "Functions.h"
#include<iostream>
#include<cstdlib>
using namespace std ;
float getConvolution_matrixmult(float *image , float *matrix ,int i ,int j , int n , int f  ){
    float sum = 0 ;
    int d  =n-f + 1 ;
    image = image + (i*d +j)*f*f ;
    for(int l = 0 ; l < f*f ; l++){
        sum += (*(matrix + l))*(*(image + l)) ;
    }
    return sum ;
}
