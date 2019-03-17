#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>

using namespace std ;

float* softmax(float* matrix, int n){
	float* prob = (float*)malloc(sizeof(float)*n) ;
	float sum  = 0 ;
	for(int i = 0 ; i < n ; i++){
		*(prob + i) = exp(*(matrix + i)) ;
		sum += *(prob + i) ;
	}
	for(int i = 0 ; i < n ; i++){
		*(prob + i) = *(prob + i)/sum ; 
	}
	
	return prob ;
}

int main() {
	int size = 10 ;
	ifstream myfile ;
	myfile.open("Layer_Outputs/fc_2.txt") ;
	float* matrix = (float*)malloc(sizeof(float)*size) ;
	float* temp  = matrix; 
	while(!myfile.eof()){
		myfile >> *temp ;
		temp++ ;
	}
	ofstream ofile2 ;
	ofile2.open("Layer_Outputs/softmax_prob.txt") ;
	matrix = softmax(matrix,size) ;
	for(int l = 0 ; l < size ; l++){
			ofile2 << *(matrix + l) << endl ;
	}
	//cout << "Chances of image being digits 0 - 9 : " << endl ;
	//for(int i = 0; i < size ; i++){
	//	cout << i << " :  " << (*(matrix + i) * 100) << " %" << endl ;
	//}
	ofile2.close() ;
	
}
