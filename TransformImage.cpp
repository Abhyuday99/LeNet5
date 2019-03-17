#include "functions.h"
#include<iostream>
#include<cstdlib>

float* TransformImage(float* image,int n , int k){
    int d  = n-k + 1 ;
    float* newarr = (float*) malloc(sizeof(int)*d*d*k*k) ;
    float* temp = newarr ;
    for(int i = 0 ; i < d ; i++){
        for(int j = 0 ; j < d ; j++){
           for(int a = 0 ; a < k ; a++ ){
                for(int b = 0 ; b < k ; b++){
                    *temp = *(image + i*n + j + a*n + b) ;
                    temp++ ;
                }
           }
        }
    }
    return newarr ;

}
