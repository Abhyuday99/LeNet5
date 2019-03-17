#include<iostream>
#include<fstream>
#include<cstdlib>
#include<math.h>
using namespace std ;

float max_pool(float *arr, int n, int f, int s, int i, int j){
	
	float max = -10000.0;
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

float* getPooled(float* image ,int n, int s,int layers){
	
	if(n % s != 0){
		cout << "Invalid input" << endl ;
		return  NULL ;
	}
	int output_size = n/s ;
	float* output = (float*)malloc(sizeof(float)*output_size*output_size*layers) ;
	for(int k = 0 ; k < layers ; k++){
		for(int i = 0 ; i < output_size ; i++){
			for(int j = 0 ; j < output_size ; j++){
			   *(output + k*output_size*output_size + i*output_size + j) = max_pool(image + k*n*n,n,s,s,i,j) ;
			}
		}
	}
	return output ;
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
	int n = 8, s= 2 , layers = 50 ; 
	ifstream myfile ;
	myfile.open("Layer_Outputs/conv_2.txt") ;
	float* image = (float*)malloc(sizeof(float)*n*n*layers) ;
	for(int i = 0 ; i < layers ; i++){
		for(int j = 0 ; j < n ; j++){
			for(int k = 0 ; k < n ; k++){
				myfile >> *(image + i*n*n + j*n + k) ;
			}
		}
	}
	//image = tanh(image,n*layers,n) ;
	float* matrix = getPooled(image,n,s,layers) ;
	ofstream ofile ; 
	ofile.open("Layer_Outputs/pool_2.txt") ;
	int output_size = n/s ;
	for(int k = 0 ; k < layers ; k++){
		for(int i = 0 ; i < output_size ; i++){
			for(int j = 0 ; j < output_size ; j++){
				ofile << *(matrix + k*output_size*output_size + i*output_size + j) << " " ;
			}
			ofile << endl ;
		}
		ofile << endl ;
	}
	
	
}
