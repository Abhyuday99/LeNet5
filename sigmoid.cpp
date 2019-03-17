#include <iostream>
#include <math.h>

#include "functions.h"

using namespace std;

float sigmoid(float f){
	
	f = -1.0*f;
	f = exp(f);
	f = 1/(1+f);
	
	return f;
}