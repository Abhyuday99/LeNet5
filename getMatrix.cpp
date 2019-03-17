#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <math.h>
#include <string>

#include "functions.h"

using namespace std; 

float* getMatrix(string s) {

    ifstream myFile;

    try{
        myFile.open(s) ;
        if(!myFile){
            throw runtime_error("File not found") ;
        }
    }
    catch(exception &e) {
        throw runtime_error(s);
    }

    float x;
    vector<float> v; 
    int counter=0;
    while(myFile >> x){
        v.push_back(x);
        counter++;
    }

    int row_count = sqrt(counter);
    if(row_count*row_count!= counter){
        cout << "Not a square matrix" << endl;
        return NULL;
    }


    float arr[row_count][row_count];
    float* i = v.data();
    for(int j=0;j<row_count;j++){
        for(int k=0;k<row_count;k++){
            arr[j][k] = *i;
            i++;
        }
    }


    float* image = (float*)malloc(sizeof(float)*counter+1);
    int l=0;
    for(int k=0;k<row_count;k++){
        for(int j=0;j<row_count;j++){
            *(image + l) = arr[j][k];
            l++;
        }
    }    
    
    *(image + l) = -1;
    
    myFile.close();
    
    return image;
}