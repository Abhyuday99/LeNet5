										** Image Processing Library **
										-------------------------------


* Introduction
---------------

This module contains several functions, coded in C++, designed to perform simple transformations on images. It serves as an image processing librray. It envelopes certain functions which are very useful in Convolutional Neural Networks. The functions are assigned certain functionalities which is discussed breifly in the next section. Apart from these functions this module contains a header file declaring all the functions present in this module and a Makefile which enables to compile the functions fastly and smartly. The next section discusses more about the functionalities of each function, header file and the Makefile.


* SubParts of Module
---------------------

This module consists of 22 subparts including this ReadMe file. There are 16 C++ files, 3 text files, 1 header file, 1 Makefile and 1 Folder. This section of ReadMe discusses of each of these subparts briefly tells about their functionalities. The Folder contains information about gnuplot and includes a time analysis between different methods of matrix multiplication.

	1. Text Files
	--------------
		1. ReadMe.txt - ReadMe is a user guide to this module and can be reffered if user is stuck at any point while using the module.

		2. matrix.txt - This file contains a sample image matrix in coloumn major order. The image matrix MUST be a SQUARE MATRIX. 

		3. kernel.txt - This file contains a sample kernel to perform several operations discussed later. The kernel matrix is also represented in coloumn major order and MUST 	also be a SQUARE MATRIX.

	2. C++ Files (functions)
	------------------------
		The C++ files on compiling generate an executable named library.
		Syntax:
			export MKLROOT= <Path of mkl library> (example: /opt/intel/mkl)  
			export LD_LIBRARY_PATH= <Path of OpenBLAS library> (example: /opt/OpenBLAS/lib/)			
			make library		

		main.cpp - This is the main function which calls all other functions. It takes the input from command line and finds suitable function to call. It then returns the results in output.txt 		file. If the number of command line arguments are not appropriate for the function user wants to perform, or file name provided by user is not correct or a wrong function name is called by 		user, it prints appropriate error messages.

		The C++ functions will be discussed in the order in which they are called in main.cpp.

		->  The first operation that can be performed using this library is to get convolution of a image matrix with a kernel matrix. The syntax to perform this operation is

		  ./library getCnvolution <file_containing_matrix.txt> <file_containing_kerenl.txt>
		
		  Main first calls the getMatrix() function to get the image matrix from the file specified by the user. It then calls the same function to get the kernel matrix from the file specified by 		  the user. It inverts the kernel using invertKernel() function Main then performs the convolution operation by calling getConvolution() function and outputs the matrix in a 2-D 			  representation in an output.txt file.

		->  The second operation is the convolution with padding of image matrix. The padding helps in controlling the size of output matrix and is an important operation in Convolutional Neural 		    Networks. The syntax for this operation is

		  ./library getConvolution_padding padding_parameter(integer) <file_containing_matrix.txt> <file_containing_kerenl.txt>
		
		  It has the same functionalities as the previous function with the exception to a call to applyPadding() to apply certain layers of padding (with 0) around the image matrix. The number of 		  layers of padding applied is provided by the user in the command line as the padding_parameter.

		->  The third operation offered is get Convolution which is implemented as matrix multiplication. The syntax for this operation is 
		  
		  ./library getConvolution_matrixmult <file_containing_matrix.txt> <file_containing_kerenl.txt>

		  It implements the convolution of matrices as matrix multiplication. It is performed by calling to a function TransformImage() which transfroms the image matrix to toeplitz matrix and 		  then getConvolution_matrixmult() which performs multiplication operation between transformed image matrix and the kernel.

		-> The fourth operation is to get Convoluion with padding and implemneted as matrix multiplication. The syntax is

		    ./library getConvolution_padding_matrixmult padding_parameter(integer) <file_containing_matrix.txt> <file_containing_kerenl.txt>

		    It has exactly same functionalities like getConvolution_padding command with the only difference being that the convolution is performed using matrix multiplication.

			-> Subparts of 3rd and 4th operation are provided:

			- User can add MKL, OpenBlas or PThread in their command and use the desired library for faster matrix multiplication.

			- Syntaxes:
			- For Matrix multilication using MKL library :
				./library getConvolution_MKL_matrixmult <file_containing_matrix.txt> <file_containing_kerenl.txt>
				
			- For Matrix multiplication after padding using MKL library:										     
				./library getConvolution_padding_MKL_matrixmult padding_parameter(integer) <file_containing_matrix.txt> <file_containing_kerenl.txt>

			- For Matrix multiplication using OpenBlas library:
				./library getConvolution_OpenBlas_matrixmult <file_containing_matrix.txt> <file_containing_kerenl.txt>

			- For Matrix multiplication after padding using OpenBlas library:										     
				./library getConvolution_padding_OpenBlas_matrixmult padding_parameter(integer) <file_containing_matrix.txt> <file_containing_kerenl.txt>

			- For Matrix multipication creating parallel threads: 
				./library getConvolution_PThread_matrixmult <file_containing_matrix.txt> <file_containing_kerenl.txt>					

			-For matrix multiplication after padding, creating parallel threads:
				./library getConvolution_padding_PThread_matrixmult padding_parameter(integer) <file_containing_matrix.txt> <file_containing_kerenl.txt>

				NOTE: User can still opt not to chooseany of these options and use the standard matrix multiplication by using previously specified command.	


		->  The fifth operation offered is to preform relu function on each matrix element. The syntax for this operation is

		    ./library relu <file_containing_matrix.txt>

		    It simply gets the matrix from the function using getMatrix() function and perfoms relu operation on each element using the relu() function.

		-> The sixth operation offered is to preform tanh function on each matrix element. The syntax for this operation is

		   ./library tanh <file_containing_matrix.txt>

		   It simply gets the matrix from the function using getMatrix() function and perfoms tanh operation on each element using the tanh() function.

		-> The seventh operaration is of max pooling. The syntax is 

		   ./library max_pooling <file_containing_matrix.txt> filter_size(integer) stride(integer)

		   This function performs the max pooling operation using the max_pool() function and returns the max_pooled matrix in the output.txt file. It takes both filter size and stride sizes from 		   user giving a flexibility.
		
		-> The eighth operaration is of average pooling. The syntax is 

		   ./library avg_pooling <file_containing_matrix.txt> filter_size(integer) stride(integer)

		   This function performs the average pooling operation using the avg_pool() function and returns the avg_pooled matrix in the output.txt file. It takes both filter size and stride sizes 		   from user giving a flexibility.

		-> The ninth operation is performed on a vector and is of sigmoid. The syntax is
		
		   ./library sigmoid <file_containing_vector.txt>

		   This function applys sigmoid operation using the sigmoid() function on each element of the vector and returns the output vector in output.txt file.

		-> The tenth operation is also performed on a vector and is of softmax. The syntax is
		
		   ./library softmax <file_containing_vector.txt>

		   This function applys softmax operation using the softmax() function on each element of the vector and returns the output vector in output.txt file.

		The names, argument types and return types of each function is provided below as well as in functions.h file.
	
	3. Header File
	--------------

	This module contains functions.h header file which declares all the functions and links all the functions of the library to each other and to main. It contains the name of functions, their return 	types and argument types. The content of functions.h along with special remarks about some of the functions is provided below.

	float getConvolution(float *image , float *kernel ,int i ,int j,int n , int f);

	float* getMatrix(std::string); 
	(This function gets the matrix from user in coloumn major form, converts it into row major form and then returns the pointer to that row major form, all operations in the library for getting a 	matrix rely on getMatrix() and thus, are designed for row major form.)
	
	float* invertKernel(float* input, int n);
	float* applyPadding(float* image,int p,int n);
	float* TransformImage(float* image, int n, int f);
	float getConvolution_matrixmult(float *image,float *matrix,int i,int j,int n,int f);
	float* relu(float* arr,int n);
	float* tanh(float* arr,int n);

	float max_pool(float *arr, int n, int f, int s, int i, int j);
	float avg_pool(float *arr, int n, int f, int s, int i, int j);
	(These functions take the stride size from user and provide flexibility to user. If the user does not mentions(forgets) stride size, the main itself assumes the stride size equal to the filter 	size and prints a warning message to warn the user that stride size is automatically fixed to filter size)

	float sigmoid(float f);
	float softmax(float f, float sum);

	float* MKL_matrixmult(int d, int k, float *arr, float* kernel, float* processed);
	float* OpenBLAS_matrixmult(int d, int k, float *arr, float* kernel, float* processed);
	
	void* PTHConvolution_matrixmult(void* ptr);
	(This is a helper function for pThread_matrixmult)

	float* pThread_matrixmult(float* A,float* B,int x,int y);

	4. Makefile
	------------

	The Makefile is a clever scripting provided to user to be able to compile programs in any given compiler without any significant efforts. The following commands are provided to the user to make 	working with so many files simpler.

	make library - This command compiles all the .cpp files and forms an executable named library. It is a smart command in the sense that if user after compiling all the files decide to modify a few 	files, this command selectively compiles only the modified files, thus reducing the load of compiler and machine which wouldn't be the case if the machine would have to compile all (13 in case of 	this small library) files even if only 1 file is slight modified.

	make clean - This command removes all .o (object files) and the executable (library) in this case.

	make <file.o> - This command can selectively compile only file.cpp and those .cpp files which are depended on file.cpp.

	Along with it's commands makefile, there is a defined variable CC, which specifies the compiler being used to compile these files, if the library files are being compiled on a machine which say, 	does not has support for GNU Compiler Collection, a small change in the makefile can save the user a lot of trouble and time. 

	It also has variables (FLAGS) which needs to be included for MKL, OpenBlas and PThread libraries. Variables are set for Mac OS Mojave 10.14 operating system. Users can find the required modification of the MKLFLAG for their system at https://software.intel.com/en-us/articles/intel-mkl-link-line-advisor/ 


	5. Folder (Time_Analysis)
	-------------------------
	This is the time analysis of various types of matrix multiplication functions. 
	This folder contains a ReadMe itself which carries more information about its subparts.



																		HAPPY NEURAL NETWORKING !!
************************************************************---------------------------------------------------*****************************************************************