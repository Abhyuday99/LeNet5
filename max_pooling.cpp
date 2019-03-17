//coloumn major order
#include <iostream>

#include "functions.h"

using namespace std;

float max_pool(float *arr, int n, int f, int s, int i, int j){
	
	float max = -1.0;
	int a,b,index_i,index_j;
	a = i*s;
	b = j*s;

	for(int x=0; x<f; x++){
		for(int y=0;y<f; y++){
			index_i = i*s + x;
			index_j = j*s + y;
			if(index_i< n && index_j< n){
				if( *(arr + (a+x)*n + j*s + y) > max){
					max = *(arr + (a+x)*n + j*s + y);
				}
			}	
		}
	}

	return max;
}
