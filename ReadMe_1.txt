This package contains 15 files including 3 .cpp files, 3 .eps files, 3.png files, 5 txt files and 1 Makefile.

The 3 cpp files are the scripts which are to be run to calculate timings of various types of matrix multiplications. 

3 txt files, 3 png files and 3 eps files contain information and plot containing information about the runtimes of the different types of matrix multiplications.

1 txt file, <gnuplot.txt> contains the command to be executed in gnuplot to obtain these different png and eps files from their txt counterparts.

1 txt file is this ReadMe.

1 Makefile is provided to compile the scripts.

	For compiling MKL_runtime_script.cpp:
		export MKLROOT=/opt/intel/mkl
		make MKL_timings
	To run the executable and obtain txt file:
	./MKL_timings 
	
	For compiling OpenBLAS_runtime_script.cpp:
		export LD_LIBRARY_PATH=/opt/OpenBLAS/lib/
		make OpenBLAS_timings
	To run the executable and obtain txt file:
	./OpenBLAS_timings

	For compiling OpenBLAS_runtime_script.cpp:
		make PThread_timings
	To run the executable and obtain txt file:
	./PThread_timings