#include <iostream>
#include <fstream>

using namespace std;

int main(){
    int size = 10;
    ifstream myfile;
    myfile.open("Layer_Outputs/softmax_prob.txt");
    float* matrix = (float*)malloc(sizeof(float)*size);
    float* temp  = matrix;
    float* head  = matrix;
    while(!myfile.eof()){
        myfile >> *temp ;
        temp++ ;
    }
    sort(head,head+10);
    ofstream ofile;
    ofile.open("best_5_values.txt");
    for(int l = 5; l < 10; l++){
        ofile << (*(matrix + l)*100.0) << " " << "%" << endl;
    }
    ofile.close();
}
