#include<iostream>
#include<fstream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"

using namespace std ;
using namespace cv ;
int main(int argc, char *argv[]) {
	if(argc < 2){
		cout << "Error: insufficient command line arguments" << endl ;
		return -1 ;
	}
	ofstream myfile ;
	myfile.open("Layer_Outputs/1_processed.txt") ;
	Mat image = imread(argv[1],0) ;
	Size s = image.size() ;
	int row = s.height ;
	int col = s.width ;
	if(row != 28 || col != 28){
		resize(image,image,Size(28,28)) ;
	}
	int temp ;
	for(int i = 0 ; i < image.rows ; i++){
		for(int j = 0 ; j < image.cols ; j++){
				temp = image.at<uchar>(i,j) ;
				myfile << temp << endl ;
			
		}
	}
	myfile.close() ;
	
	


}
