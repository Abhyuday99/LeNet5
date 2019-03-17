#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <pthread.h>

#include "functions.h"

using namespace std;

int n,k,d;
float *matrix, *image, *kernel;


int main(int argc, char* argv[]){

    
    // takes in input: input image matrix file input kernel matrix file and outputs the convoluted matrix in output.txt file
    if(!strcmp(argv[1],"getConvolution")){

        if(argc != 4){
            cout << "Invalid number of command-line arguments" << endl;
            return 0;
        }

        float* kernel_in;

        try{
            image = getMatrix(argv[2]);
            if(image == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[2] << " file not found" << endl;
            return 0;
        }

        try{
            kernel_in = getMatrix(argv[3]);
            if(kernel_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[3] << " file not found" << endl;
        }

        float* q = image;
        for(n=0;*q!=-1;n++){
            q=q+1;
        }
        n = sqrt(n);

        q = kernel_in;
        for(k=0;*q!=-1;k++){
            q=q+1;
        }
        k = sqrt(k);

        kernel = invertKernel(kernel_in,k);

        d = n-k+1;

        ofstream outFile;
        outFile.open("output.txt");

        float* processed = (float*)malloc(sizeof(float)*d*d);
        for(int i =0;i<d;i++){
            for(int j=0;j<d;j++){
                *(processed + i*d + j) = getConvolution(image,kernel,i,j,n,k);
                outFile << *(processed + i*d + j) << " " ;
            }
            outFile << endl;
        }
        outFile.close();
    }

    
    //takes input the padding parameter, matrix file and kernel file and outputs the convolved matrix in output.txt
    else if(!strcmp(argv[1],"getConvolution_padding")){

        if(argc != 5){
            cout << "Invalid number of command-line arguments" << endl ;
            return 0 ;
        }

        float* image_in;
        float* kernel_in;

        try{
            image_in = getMatrix(argv[3]);
            if(image_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[3] << " file not found" << endl;
            return 0;
        }

        try{
            kernel_in = getMatrix(argv[4]);
            if(kernel_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[4] << " file not found" << endl;
        }

        float* q = image_in;
        for(n=0;*q!=-1;n++){
            q=q+1;
        }
        n = sqrt(n);

        q = kernel_in;
        for(k=0;*q!=-1;k++){
            q=q+1;
        }
        k = sqrt(k);

        kernel = invertKernel(kernel_in,k);

        d = atoi(argv[2]);

        ofstream outFile;
        outFile.open("output.txt");

        image = applyPadding(image_in,d,n);
        int newsize = n+2*d;
        float* processed = (float*)malloc(sizeof(float)*newsize*newsize);
        for(int i = 0;i< newsize-k+1;i++){
            for(int j = 0;j< newsize-k+1;j++){
                *(processed+i*newsize+j) = getConvolution(image,kernel,i,j,newsize,k) ;
                outFile << *(processed+i*newsize+j) << " " ;
            }
            outFile << endl;
         }
    }

    
    //takes an imaeg file and a kernel file as an input and gives the output in output.txt file
    else if(!strcmp(argv[1],"getConvolution_matrixmult")){

        if(argc != 4){
            cout << "Invalid number of command-line arguments" << endl ;
            return 0 ;
        }

        float* image_in;
        float* kernel_in;

        try{
            image_in = getMatrix(argv[2]);
            if(image_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[2] << " file not found" << endl;
            return 0;
        }

        try{
            kernel_in = getMatrix(argv[3]);
            if(kernel_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[3] << " file not found" << endl;
        }

        float* q = image_in;
        for(n=0;*q!=-1;n++){
            q=q+1;
        }
        n = sqrt(n);

        q = kernel_in;
        for(k=0;*q!=-1;k++){
            q=q+1;
        }
        k = sqrt(k);

        kernel = invertKernel(kernel_in,k);

        d = n-k+1;

        ofstream outFile;
        outFile.open("output.txt");

        image_in = TransformImage(image_in,n,k) ;
        float* processed = (float*)malloc(sizeof(float)*d*d);
        for(int i = 0;i< d;i++){
            for(int j = 0;j< d;j++){
                *(processed+i*d+j) = getConvolution_matrixmult(image_in,kernel,i,j,n,k);
                outFile << *(processed+i*d+j) << " ";
            }
            outFile << endl;
        }

        outFile.close();
    }

    
    //takes in input the padding parameter, image file, kernel file and outputs the convolved result in output.txt
    else if(!strcmp(argv[1],"getConvolution_padding_matrixmult")){

        if(argc != 5){
            cout << "Invalid number of command-line arguments" << endl;
            return 0;
        }

        float* image_in;
        float* kernel_in;
        d = atoi(argv[2]);

        try{
            image_in = getMatrix(argv[3]);
            if(image_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[3] << " file not found" << endl;
            return 0;
        }

        try{
            kernel_in = getMatrix(argv[4]);
            if(kernel_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[4] << " file not found" << endl;
        }

        float* q = image_in;
        for(n=0;*q!=-1;n++){
            q=q+1;
        }
        n = sqrt(n);

        q = kernel_in;
        for(k=0;*q!=-1;k++){
            q=q+1;
        }
        k = sqrt(k);

        kernel = invertKernel(kernel_in,k) ;
        image = applyPadding(image_in,d,n) ;

        int newsize = n + 2*d;
        int output_size = newsize -k + 1;
        float* processed = (float*)malloc(sizeof(float)*output_size*output_size);


        image = TransformImage(image,newsize,k);

        ofstream outFile;
        outFile.open("output.txt");

        for(int i = 0;i< output_size;i++){
            for(int j = 0;j< output_size;j++){
                *(processed + i*output_size + j) = getConvolution_matrixmult(image,kernel,i,j,newsize,k) ;
                outFile << *(processed + i*output_size + j) << " " ;
            }
            outFile << endl ;
        }

        outFile.close();
    }

    
    //Gets the convolution through MKL Matrix multiplication function, takes input the matrix.txt and kernel.txt files and gives as output output.txt
    else if(!strcmp(argv[1],"getConvolution_MKL_matrixmult")){

            if(argc != 4){
            cout << "Invalid number of command-line arguments" << endl ;
            return 0 ;
        }

        float* image_in;
        float* kernel_in;

        try{
            image_in = getMatrix(argv[2]);
            if(image_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[2] << " file not found" << endl;
            return 0;
        }

        try{
            kernel_in = getMatrix(argv[3]);
            if(kernel_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[3] << " file not found" << endl;
        }

        float* q = image_in;
        for(n=0;*q!=-1;n++){
            q=q+1;
        }
        n = sqrt(n);

        q = kernel_in;
        for(k=0;*q!=-1;k++){
            q=q+1;
        }
        k = sqrt(k);

        kernel = invertKernel(kernel_in,k);

        d = n-k+1;

        ofstream outFile;
        outFile.open("output.txt");

        image_in = TransformImage(image_in,n,k) ;
        float* processed = (float*)malloc(sizeof(float)*d*d);
        processed = MKL_matrixmult(d,k,image_in,kernel,processed);
        for(int i = 0;i< d;i++){
            for(int j = 0;j< d;j++){
                outFile << *(processed+i*d+j) << " ";
            }
            outFile << endl;
        }

        outFile.close();
    }

    
    //Gets the convolution through OpenBLAS Matrix multiplication function, takes input the matrix.txt and kernel.txt files and gives as output output.txt
    else if(!strcmp(argv[1],"getConvolution_OpenBLAS_matrixmult")){

        if(argc != 4){
            cout << "Invalid number of command-line arguments" << endl ;
            return 0 ;
        }

        float* image_in;
        float* kernel_in;

        try{
            image_in = getMatrix(argv[2]);
            if(image_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[2] << " file not found" << endl;
            return 0;
        }

        try{
            kernel_in = getMatrix(argv[3]);
            if(kernel_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[3] << " file not found" << endl;
        }

        float* q = image_in;
        for(n=0;*q!=-1;n++){
            q=q+1;
        }
        n = sqrt(n);

        q = kernel_in;
        for(k=0;*q!=-1;k++){
            q=q+1;
        }
        k = sqrt(k);

        kernel = invertKernel(kernel_in,k);

        d = n-k+1;

        ofstream outFile;
        outFile.open("output.txt");

        image_in = TransformImage(image_in,n,k) ;
        float* processed = (float*)malloc(sizeof(float)*d*d);
        processed = OpenBLAS_matrixmult(d,k,image_in,kernel,processed);
        for(int i = 0;i< d;i++){
            for(int j = 0;j< d;j++){
                outFile << *(processed+i*d+j) << " ";
            }
            outFile << endl;
        }

        outFile.close();
    }
    
    // Gets the convolution through PThread Matrix multiplication function, it takes input the matrix.txt and kernel.txt files and gives as output output.txt
    else if(!strcmp(argv[1],"getConvolution_PThread_matrixmult")){

        if(argc != 4){
            cout << "Invalid number of command-line arguments" << endl ;
            return 0 ;
        }

        float* image_in;
        float* kernel_in;

        try{
            image_in = getMatrix(argv[2]);
            if(image_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[2] << " file not found" << endl;
            return 0;
        }

        try{
            kernel_in = getMatrix(argv[3]);
            if(kernel_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[3] << " file not found" << endl;
        }
        float* q = image_in;
        for(n=0;*q!=-1;n++){
            q=q+1;
        }
        n = sqrt(n);

        q = kernel_in;
        for(k=0;*q!=-1;k++){
            q=q+1;
        }
        k = sqrt(k);

        kernel = invertKernel(kernel_in,k);

        d = n-k+1;
        
        ofstream outFile;
        outFile.open("output.txt");

        //image_in = TransformImage(image_in,n,k) ;
        float* processed = (float*)malloc(sizeof(float)*d*d);
        processed = pThread_matrixmult(image_in,kernel,n,k);        
        for(int i = 0;i< d;i++){
            for(int j = 0;j< d;j++){
                outFile << *(processed+i*d+j) << " ";
            }
            outFile << endl;
        }

        outFile.close();
    }
    
    //Gets the convolution through MKL Matrix multiplication function, takes input the padding parameter, matrix.txt and kernel.txt files and gives as output output.txt
    else if(!strcmp(argv[1],"getConvolution_padding_MKL_matrixmult")){

        if(argc != 5){
            cout << "Invalid number of command-line arguments" << endl;
            return 0;
        }

        float* image_in;
        float* kernel_in;
        d = atoi(argv[2]);

        try{
            image_in = getMatrix(argv[3]);
            if(image_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[3] << " file not found" << endl;
            return 0;
        }

        try{
            kernel_in = getMatrix(argv[4]);
            if(kernel_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[4] << " file not found" << endl;
        }

        float* q = image_in;
        for(n=0;*q!=-1;n++){
            q=q+1;
        }
        n = sqrt(n);

        q = kernel_in;
        for(k=0;*q!=-1;k++){
            q=q+1;
        }
        k = sqrt(k);

        kernel = invertKernel(kernel_in,k) ;
        image = applyPadding(image_in,d,n) ;

        int newsize = n + 2*d;
        int output_size = newsize -k + 1;
        float* processed = (float*)malloc(sizeof(float)*output_size*output_size);


        image = TransformImage(image,newsize,k);

        ofstream outFile;
        outFile.open("output.txt");
        
        processed = MKL_matrixmult(output_size,k,image,kernel,processed);
        for(int i = 0;i< output_size;i++){
            for(int j = 0;j< output_size;j++){
                outFile << *(processed + i*output_size + j) << " " ;
            }
            outFile << endl ;
        }

        outFile.close();
    }

    
    //Gets the convolution through OpenBLAS Matrix multiplication function, takes input the padding parameter, matrix.txt and kernel.txt files and gives as output output.txt
    else if(!strcmp(argv[1],"getConvolution_padding_OpenBLAS_matrixmult")){

        if(argc != 5){
            cout << "Invalid number of command-line arguments" << endl;
            return 0;
        }

        float* image_in;
        float* kernel_in;
        d = atoi(argv[2]);

        try{
            image_in = getMatrix(argv[3]);
            if(image_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[3] << " file not found" << endl;
            return 0;
        }

        try{
            kernel_in = getMatrix(argv[4]);
            if(kernel_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[4] << " file not found" << endl;
        }

        float* q = image_in;
        for(n=0;*q!=-1;n++){
            q=q+1;
        }
        n = sqrt(n);

        q = kernel_in;
        for(k=0;*q!=-1;k++){
            q=q+1;
        }
        k = sqrt(k);

        kernel = invertKernel(kernel_in,k) ;
        image = applyPadding(image_in,d,n) ;

        int newsize = n + 2*d;
        int output_size = newsize -k + 1;
        float* processed = (float*)malloc(sizeof(float)*output_size*output_size);


        image = TransformImage(image,newsize,k);

        ofstream outFile;
        outFile.open("output.txt");

        processed = OpenBLAS_matrixmult(output_size,k,image,kernel,processed);
        for(int i = 0;i< output_size;i++){
            for(int j = 0;j< output_size;j++){
                outFile << *(processed + i*output_size + j) << " " ;
            }
            outFile << endl ;
        }

        outFile.close();
    }

    //Gets the convolution through PThread Matrix multiplication function, takes input the padding parameter, matrix.txt and kernel.txt files and gives as output output.txt
    else if(!strcmp(argv[1],"getConvolution_padding_PThread_matrixmult")){

        if(argc != 5){
            cout << "Invalid number of command-line arguments" << endl;
            return 0;
        }

        float* image_in;
        float* kernel_in;
        d = atoi(argv[2]);

        try{
            image_in = getMatrix(argv[3]);
            if(image_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[3] << " file not found" << endl;
            return 0;
        }

        try{
            kernel_in = getMatrix(argv[4]);
            if(kernel_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[4] << " file not found" << endl;
        }

        float* q = image_in;
        for(n=0;*q!=-1;n++){
            q=q+1;
        }
        n = sqrt(n);

        q = kernel_in;
        for(k=0;*q!=-1;k++){
            q=q+1;
        }
        k = sqrt(k);

        kernel = invertKernel(kernel_in,k) ;
        image = applyPadding(image_in,d,n) ;

        int newsize = n + 2*d;
        int output_size = newsize -k + 1;
        float* processed = (float*)malloc(sizeof(float)*output_size*output_size);


        image = TransformImage(image,newsize,k);

        ofstream outFile;
        outFile.open("output.txt");

        processed = pThread_matrixmult(image,kernel,n,k);
        for(int i = 0;i< output_size;i++){
            for(int j = 0;j< output_size;j++){
                outFile << *(processed + i*output_size + j) << " " ;
            }
            outFile << endl ;
        }

        outFile.close();
    }

    
    //takes input matrix, applies relu function on each element and output the result in output.txt
    else if(!strcmp(argv[1],"relu")){

        if(argc != 3){
            cout << "Invalid number of command-line arguments" << endl ;
            return 0 ;
        }

        float* image_in;

        try{
            image_in = getMatrix(argv[2]);
            if(image_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[2] << " file not found" << endl;
            return 0;
        }

        float* q = image_in;
        for(n=0;*q!=-1;n++){
            q=q+1;
        }
        n = sqrt(n);

        ofstream outFile;
        outFile.open("output.txt");

        float* processed = relu(image_in,n) ;

        for(int i = 0;i< n;i++){
            for(int j = 0;j< n;j++){
                outFile << *(processed + i*n + j) << " ";
            }
            outFile << endl;
        }

        outFile.close();
    }

    
    //takes input matrix, applies tanh function on each element and output the result in output.txt
    else if(!strcmp(argv[1],"tanh")){

        if(argc != 3){
            cout << "Invalid number of command-line arguments" << endl ;
            return 0 ;
        }

        float* image_in;

        try{
            image_in = getMatrix(argv[2]);
            if(image_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[2] << " file not found" << endl;
            return 0;
        }

        float* q = image_in;
        for(n=0;*q!=-1;n++){
            q=q+1;
        }
        n = sqrt(n);

        ofstream outFile;
        outFile.open("output.txt");

        float* processed = tanh(image_in,n) ;

        for(int i = 0;i< n;i++){
            for(int j = 0;j< n;j++){
                outFile << *(processed + i*n + j) << " ";
            }
            outFile << endl;
        }

        outFile.close();
    }

    
    //takes input the matrix file, filter size and stride size and outputs the matrix in output.txt
    else if(!strcmp(argv[1],"max_pooling")){

        if(argc != 5 && argc !=4){
            cout << "Invalid number pf command-line arguments" << endl;
            return 0;
        }

        int f,s;
        if(argc == 4){
            cout << "Warning! Stride size not provided, set default to filter size (=" << argv[3] << ")." << endl;
            f = atoi(argv[3]);
            s = atoi(argv[3]);
        }
        else if(argc == 5){
            f = atoi(argv[3]);
            s = atoi(argv[4]);
        }

        float* image_in;

        try{
            image_in = getMatrix(argv[2]);
            if(image_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[2] << " file not found" << endl;
            return 0;
        }

        float* q = image_in;
        for(n=0;*q!=-1;n++){
            q=q+1;
        }
        n = sqrt(n);

        int output_size;
        if(n%s==0)
            output_size = n/s;
        else
            output_size = n/s +1;

        float* processed = (float*)malloc(sizeof(float)*output_size*output_size);

        ofstream outFile;
        outFile.open("output.txt");

        for(int i=0;i<output_size;i++){
            for(int j=0;j<output_size;j++){
                *(processed + i*output_size + j) = max_pool(image_in, n, f, s, i, j);
                outFile << *(processed + i*output_size + j) << " ";
            }
            outFile << endl;
        }

        outFile.close();
    }

    
    //takes input the matrix file, filter size and stride size and outputs the matrix in output.txt
    else if(!strcmp(argv[1],"avg_pooling")){

        if(argc != 5 && argc !=4){
            cout << "Invalid number pf command-line arguments" << endl;
            return 0;
        }

        int f,s;
        if(argc == 4){
            cout << "Warning! Stride size not provided, set default to filter size (=" << argv[3] << ")." << endl;
            f = atoi(argv[3]);
            s = atoi(argv[3]);
        }
        else if(argc == 5){
            f = atoi(argv[3]);
            s = atoi(argv[4]);
        }

        float* image_in;

        try{
            image_in = getMatrix(argv[2]);
            if(image_in == NULL){
                return 0;
            }
        }
        catch(exception e){
            cout << argv[2] << " file not found" << endl;
            return 0;
        }

        float* q = image_in;
        for(n=0;*q!=-1;n++){
            q=q+1;
        }
        n = sqrt(n);

        int output_size;
        if(n%s==0)
            output_size = n/s;
        else
            output_size = n/s +1;

        float* processed = (float*)malloc(sizeof(float)*output_size*output_size);

        ofstream outFile;
        outFile.open("output.txt");

        for(int i=0;i<output_size;i++){
            for(int j=0;j<output_size;j++){
                *(processed + i*output_size + j) = avg_pool(image_in, n, f, s, i, j);
                outFile << *(processed + i*output_size + j) << " ";
            }
            outFile << endl;
        }

        outFile.close();
    }

    
    //takes a file containing vector as an input and ouputs a file after applying sigmoid function to each element.
    else if(!strcmp(argv[1],"sigmoid")){

        if(argc != 3){
            cout << "Invalid number pf command-line arguments" << endl;
            return 0;
        }

        string s = argv[2];
        ifstream myFile;

        try{
            myFile.open(s.c_str());
            if(!myFile){
                cout <<  argv[2] << " file not found" << endl;
                return 0;
            }
        }
        catch(exception e){}

        float x;
        vector <float> v;
        int row_count=0;
        while(myFile >> x){
            v.push_back(x);
            row_count++;
        }
        myFile.close();

        ofstream outFile;
        outFile.open("output.txt");

        for(int i=0;i<row_count;i++){
            outFile << sigmoid(v.at(i)) << " " << endl;
        }

        outFile.close();
    }

    
    //takes a file containing vector as an input and ouputs a file after applying softmax function to each element.
    else if(!strcmp(argv[1],"softmax")){

        if(argc != 3){
            cout << "Invalid number pf command-line arguments" << endl;
            return 0;
        }

        string s = argv[2];
        ifstream myFile;

        try{
            myFile.open(s.c_str());
            if(!myFile){
                cout <<  argv[2] << " file not found" << endl;
                return 0;
            }
        }
        catch(exception e){}

        float x,sum=0.0;
        vector <float> v;
        int row_count=0;
        while(myFile >> x){
            v.push_back(x);
            row_count++;
            sum = sum + exp(x);
        }
        myFile.close();

        ofstream outFile;
        outFile.open("output.txt");

        for(int i=0;i<row_count;i++){
            outFile << softmax(v.at(i),sum) << " " << endl;
        }

        outFile << endl;
        myFile.close();
    }

    
    //When user calls a function not defined in library
    else{

        cout << "Unknown function to call" << endl;
    }

    return 0;
}
