#include<iostream>
#include<fstream>
#include <math.h>
#include "mkl.h"

using namespace std ;

float* TransformInputChannel(float* image,int n , int k,int layers){
    int d  = n-k + 1 ;
    float* newarr = (float*)mkl_malloc(sizeof(float)*d*d*(k*k*layers + 1),64) ;
    float* temp = newarr ;
    int q,r ;
    for(int i = 0 ; i < d ; i++){
	for(int j = 0 ; j < d ; j++){
	       *temp = 1 ;
	       temp++ ;
		for(int l = 0 ; l < layers ; l++){
		   
		   for(int a = 0 ; a < k ; a++ ){
		        for(int b = 0 ; b < k ; b++){
		            *temp = *(image + l*n*n + i*n + j + a*n + b) ;
		            temp++ ;
		        }
		   }
		}
	    }
    }
    return newarr ;

}

float* relu(float* arr,int n,int m){

    float* output = (float*) malloc(sizeof(float)*n*m) ;
    float* temp = arr ;
    float entry ;
    for(int i = 0 ; i < n ; i++){

        for(int j = 0 ; j < m ; j++){
            entry = *(temp + i*m + j);
           if(entry > 0){
                *(output + i*m + j) = entry ;
           }
           else{
                *(output + i*m + j) = 0 ;
           }
        }
    }
    
    return output ;
}

int main() {
	int n = 4 , k = 4,input_layers = 50,output_layers = 500 ;
	int d = n-k+1 ;
	ifstream myfile;
	myfile.open("Layer_Outputs/pool_2.txt") ;
	float* image = (float*)mkl_malloc(sizeof(float)*input_layers*n*n,64) ;
	float* temp = image ;
	float val ;
	while(!myfile.eof()){
		myfile >> val ;
		*temp = val  ;
		temp = temp + 1 ;
	}
	
	myfile.close() ;
	ifstream myfile2 ;
	myfile2.open("Weights/fc1_weights.txt") ;
	float* weights = (float*)mkl_malloc(sizeof(float)*(input_layers*k*k+1)*output_layers,64) ;
	float* temp2 = weights ;
	while(!myfile2.eof()){
		myfile2 >> (*temp2) ;
		temp2 = temp2 + 1 ;
	}
	
	float* kernel = (float*)mkl_malloc(sizeof(float)*output_layers*(input_layers*k*k + 1),64) ;
	for(int i = 0 ; i < output_layers ; i++){
		*(kernel + i) = *(weights + input_layers*k*k*output_layers + i) ;
	}
	
	for(int i = 0 ; i < output_layers  ; i++){
		for(int j = 0 ; j < k*k*input_layers ; j++){ 
			*(kernel  + output_layers + j*output_layers + i) = *(weights + j + i*k*k*input_layers) ;
		}
	}
	mkl_free(weights) ;
	float* processed = TransformInputChannel(image,n,k,input_layers) ;
	mkl_free(image) ;
	float* matrix = (float*)mkl_malloc(sizeof(float)*output_layers*d*d,64) ;
	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                d*d,output_layers,k*k*input_layers+1, 1.0, processed, input_layers*k*k+1, kernel, output_layers, 0.0, matrix, output_layers);
	

	
	ofstream ofile ;
	ofile.open("Layer_Outputs/fc_1.txt") ;
	matrix = relu(matrix,d*d,output_layers) ;
	for(int k = 0 ; k < output_layers ; k++){
		for(int i = 0 ; i < d ; i++){
			for(int j = 0 ; j < d ; j++){
				ofile << *(matrix + (i*d + j)*output_layers + k) << " " ;
			}
			ofile << endl ;
		}
		ofile << endl ;
	}
	mkl_free(processed) ;
	mkl_free(kernel) ;
	mkl_free(matrix) ;
	

	
	
	


}
