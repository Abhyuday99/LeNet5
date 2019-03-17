#include<iostream>
#include<cstdlib>
#include <pthread.h>
#include<fstream>
#include <chrono>
#define num_thread 4 
using namespace std ;

pthread_t* threads;
int n ;
float *image,*kernel,*matrix,*arr ;
int* oldstate ;
float* TransformImage(float* image,int n){
    
    float* newarr = (float*)malloc(sizeof(float)*n*n) ;
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
			*(newarr + i*n + j) = *(image + j*n + i) ;
        }
    }
    return newarr ;

}

void* get_matrixmult(void* ptr){
    int index = *((int*)ptr) ;
	int q = index/n ;
	int rem = index % n ;
    //cout << "index: " <<index << endl ;
    float sum = 0 ;
	float* temp2 = image +  q*n ;
    float* temp = arr + rem*n ;
    //cout << "num: " << *temp << endl ;
    for(int l = 0 ; l < n ; l++){
        //cout << "TEST " ; 
	    sum += (*(temp2 + l))*(*(temp + l)) ;
	    //cout << "TEST " ; 
    }
    *(matrix + index) = sum ;
    pthread_exit(NULL) ;
}

double getrunTime(float* A , int size){
    n = size ;
    //cout << n << endl ;
    arr = TransformImage(A,size) ;
    //cout << "Test" << endl ;
    matrix = (float*)malloc(sizeof(float)*n*n) ;
    //cout << "Test" << endl ;
	int* indexes = (int*)malloc(sizeof(int)*n*n) ;
	for(int i = 0 ; i < size*size ; i++){
		*(indexes + i) = i ;
	}
	auto start = chrono::high_resolution_clock::now();
	threads = (pthread_t*)malloc(sizeof(pthread_t)*num_thread) ;
	int i = 0 ; 
	int j ;
	while(i < size*size) {
	    //cout << "Test3" << endl ;
		j = i % num_thread ;
		pthread_create(&threads[j],NULL,&get_matrixmult,(void*)(indexes + i)) ;
		i++ ;
		if(j == num_thread - 1){
			for(int i = 0 ; i < num_thread ;i++){
				pthread_join(threads[i],NULL) ;
			}
		}
		//pthread_join(threads[i%num_thread],NULL) ;
		//pthread_join(threads[i],NULL) ;
	}
	//cout << "T1" << endl ;
	/*for(int i = 0 ; i < num_thread ;i++){
		pthread_join(threads[i],NULL) ;
	}*/
	//cout << "T2" << endl ;
	auto end = chrono::high_resolution_clock::now();
	double time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time *= 1e-9;
	free(threads) ;
	free(indexes) ;
	free(matrix) ;
	return time;
}


int main() {
	ofstream myfile;
	myfile.open ("PThread_timings.csv");
  	
  	
	for(int i = 2 ; i < 500 ; i+= 10 ){
	    cout << i << endl ;
	    double sum = 0 ;
	    double max = 0.0;
		double min = 10.0;	
	    for(int j = 0 ; j < 11 ; j++){
	        image = (float*)malloc(sizeof(float)*i*i) ;
	        for(int k = 0 ; k < i*i ; k++){
	            *(image + k) = rand()/(double)(RAND_MAX) ;
	        }
	         
	        double time = getrunTime(image,i) ;
	        if(j != 0){
	            sum += time ;
	            if(max < time) max = time;
				if(min > time) min = time;
	        }
	        free(image) ;
	    }
	    	myfile << i << "	" << sum/10 << "	" << min << "	" << max << endl;
	//cout << "TEST" << endl ;
	    
	}
	myfile.close();

		

}
