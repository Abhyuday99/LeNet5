#include<iostream>
#include<fstream>
#include <math.h>
#include "mkl.h"

using namespace std ;

float* TransformImage(float* image,int n , int k){
    int d  = n-k + 1 ;
    float* newarr = (float*)mkl_malloc(sizeof(float)*d*d*(k*k+1),64) ;
    float* temp = newarr ;
    int q,r ;
    for(int i = 0 ; i < d ; i++){
        for(int j = 0 ; j < d ; j++){
           *temp = 1 ;
	   temp++ ;
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

float* tanh(float* arr,int n,int m){

    float* output = (float*) malloc(sizeof(float)*n*m);
    float* temp = arr;
    float entry,result;
    for(int i = 0;i< n;i++){
        for(int j = 0;j< m;j++){
            entry = *(temp + i*m + j);
            result = exp(2*entry);
            *(output + i*m + j) = (result-1)/(result + 1);
        }
    }

    return output;
}

int main() {
	int n = 28 , k = 5,layers = 20 ;
	int d = n-k+1 ;
	ifstream myfile;
	myfile.open("Layer_Outputs/1_processed.txt") ;
	float* image = (float*)mkl_malloc(sizeof(float)*n*n,64) ;
	float* temp = image ;
	float val ;
	float mean = 0  ;
	while(!myfile.eof()){
		myfile >> val ;
		val = 1 - val/255.0 ;
		*temp = val  ;
		temp = temp + 1 ;
	}
	
	myfile.close() ;
	ifstream myfile2 ;
	myfile2.open("Weights/conv1_weights.txt") ;
	
	float* weights = (float*)mkl_malloc(sizeof(float)*layers*(k*k+1),64) ;
	float* temp2 = weights ;
	while(!myfile2.eof()){
		myfile2 >> (*temp2) ;
		temp2 = temp2 + 1 ;
	}
	
	float* kernel = (float*)mkl_malloc(sizeof(float)*layers*(k*k+1),64) ;
	for(int i = 0 ; i < 20 ; i++){
		*(kernel + i) = *(weights + 500 + i) ;
	}
	for(int i = 0 ; i < 20  ; i++){
		for(int j = 0 ; j < 25 ; j++){ 
			*(kernel  + 20 + j*20 + i) = *(weights + j + i*25) ;
		}
	}
	mkl_free(weights) ;
	float* processed = TransformImage(image,28,5) ;
	mkl_free(image) ;
	float* matrix = (float*)mkl_malloc(sizeof(float)*layers*d*d,64) ;
	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                d*d,layers,k*k+1, 1.0, processed, k*k+1, kernel, layers, 0.0, matrix, layers);
	
	ofstream ofile ;
	ofile.open("Layer_Outputs/conv_1.txt") ;
	for(int k = 0 ; k < layers ; k++){
		for(int i = 0 ; i < d ; i++){
			for(int j = 0 ; j < d ; j++){
				ofile << *(matrix + (i*d + j)*layers + k) << " " ;
			}
			ofile << endl ;
		}
		ofile << endl ;
	}

	mkl_free(processed) ;
	mkl_free(kernel) ;
	mkl_free(matrix) ;
	

	
	
	


}
