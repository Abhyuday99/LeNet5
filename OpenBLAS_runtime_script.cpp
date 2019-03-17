#include <cblas.h>
#include <iostream>
#include <cstdlib>
#include<ctime>
#include<fstream>
#include <chrono>
using namespace std ;



double getRunTime(float* A,int size) {
	float* matrix = (float*)malloc(sizeof(float)*size*size) ;
    auto start = chrono::high_resolution_clock::now();
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                size,size,size, 1.0, A, size, A, size, 0.0, matrix, size);
    auto end = chrono::high_resolution_clock::now();
    double time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time *= 1e-9;
    return time ;
	

} 


int main() {
	
	ofstream myfile;
	myfile.open ("OpenBlas_timings.txt");
	
	for(int i = 2 ; i < 500 ; i += 10){
		cout << i << endl ;
		double sum = 0 ;
        double max = 0.0;
        double min = 10.0;
		for(int k = 0 ; k < 101 ; k++) {
			float* A = (float*)malloc(sizeof(float)*i*i) ;
			for(int j = 0 ; j < i*i ; j++){
				*(A + j) = rand()/double(RAND_MAX) + rand() ;
			}
			double time = getRunTime(A,i) ;
			if(k != 0){
				sum += time ;
                if(max < time) max = time;
                if(min > time) min = time;
			}
			free(A) ;
		}
        myfile << i << "    " << sum/100 << "    " << min << "    " << max << endl;
    }
	myfile.close() ;

}
