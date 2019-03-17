#include <iostream>
#include <math.h>

#include "functions.h"

using namespace std;

float softmax(float f, float sum){
	f = exp(f);
	f = f/sum;
	
	return f;
}