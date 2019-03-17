#include<iostream>
#include<cstdlib>
#include <thread>
#include "functions.h"
#include <math.h>
#include <fstream>

using namespace std ;

int n2,k2,cores;
float *image2,*kernel2,*matrix2,*arr;

void* PTHConvolution_matrixmult(void* ptr){
    
    int index = *((int*)ptr) ;
    float sum = 0 ;
    int d  =n2-k2 + 1 ;
    float* temp = arr + index*k2*k2 ;
    for(int l = 0 ; l < k2*k2 ; l++){
        sum += (*(kernel2 + l))*(*(temp + l)) ;
    }
    *(matrix2 + index) = sum ;
    pthread_exit(NULL) ;
    
}

float* pThread_matrixmult(float* A,float* B,int x,int y){
    
    n2 = x;
    k2 = y;
    image2 = A;
    kernel2 = B;
    int d =  n2-k2+1;
    matrix2 = (float*)malloc(sizeof(float)*d*d);
    arr = TransformImage(image2,n2,k2);
    
    cores = thread::hardware_concurrency();
    pthread_t threads[cores];
    int* indexes = (int*)malloc(sizeof(int)*d*d);
    for(int i = 0 ; i < d*d ; i++){
        *(indexes + i) = i;
    }
    
    int j,i = 0 ;
    while(i < d*d){
        j = i % cores ;
        pthread_create(&threads[j],NULL,&PTHConvolution_matrixmult,(void*)(indexes + i));
        i++ ;
        if(j == cores - 1){
            for(int z = 0 ; z < cores ;z++){
                pthread_join(threads[z],NULL);
            }
        }
    }
    for(int z = 0 ; z < cores ;z++){
        pthread_join(threads[z],NULL) ;
    }
    return matrix2 ;
}


