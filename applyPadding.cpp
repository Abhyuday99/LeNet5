#include <iostream>

#include "functions.h"

using namespace std;

float* applyPadding(float* image,int p,int n){

    int newsize = n+2*p;
    float* arr = (float*)malloc(sizeof(int)*(newsize)*(newsize)) ;
    float* temp = arr;
    
    for(int i=0;i<p;i++){
        for(int j=0;j<newsize;j++){
            *temp = 0;
            temp++;
        }
    }

    for(int i= 0;i< n;i++){
        for(int j=0;j< p;j++){
            *temp = 0;
             temp++;
        }
        for(int j= 0;j < n;j++){
            *temp = *image;
            temp++;
            image++;
        }
        for(int j=0;j< p;j++){
            *temp = 0 ;
            temp++;
        }
    }
    
    for(int i=0;i< p;i++){
        for(int j=0;j< newsize;j++){
            *temp = 0;
            temp++;
        }
    }
    
    return arr;
}