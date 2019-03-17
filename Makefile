#FORMAT
#target: dependency
	#command

CC = g++ #type of compiler used 
CFLAGS = -c -Wall # Wall is warning command	

# export LD_LIBRARY_PATH=/opt/OpenBLAS/lib/
# export MKLROOT=/opt/intel/mkl

CBLASFLAG = -I /opt/OpenBLAS/include/ -L/opt/OpenBLAS/lib -lopenblas
MKLFLAG =  ${MKLROOT}/lib/libmkl_intel_ilp64.a ${MKLROOT}/lib/libmkl_sequential.a ${MKLROOT}/lib/libmkl_core.a -lpthread -lm -ldl  -DMKL_ILP64 -m64 -I${MKLROOT}/include
PTFLAG = -pthread

library: getConvolution.o getMatrix.o invertkernel.o applyPadding.o TransformImage.o getConvolution_matrixmult.o relu.o tanh.o max_pooling.o avg_pooling.o sigmoid.o softmax.o
	$(CC) -o library $(PTFLAG) getConvolution.o getMatrix.o invertkernel.o applyPadding.o TransformImage.o getConvolution_matrixmult.o relu.o tanh.o max_pooling.o avg_pooling.o sigmoid.o softmax.o MKL_matrixmult.cpp OpenBLAS_matrixmult.cpp PThread_matrixmult.cpp main.cpp $(MKLFLAG) $(CBLASFLAG)
	 
getConvolution.o: getConvolution.cpp	
	$(CC) $(CFLAGS) getConvolution.cpp

getMatrix.o: getMatrix.cpp
	$(CC) $(CFLAGS) getMatrix.cpp

invertkernel.o: invertkernel.cpp
	$(CC) $(CFLAGS) invertkernel.cpp

applyPadding.o: applyPadding.cpp
	$(CC) $(CFLAGS) applyPadding.cpp

TransformImage.o: TransformImage.cpp
	$(CC) $(CFLAGS) TransformImage.cpp

getConvolution_matrixmult.o: getConvolution_matrixmult.cpp
	$(CC) $(CFLAGS) getConvolution_matrixmult.cpp	

relu.o: relu.cpp
	$(CC) $(CFLAGS) relu.cpp

tanh.o: tanh.cpp
	$(CC) $(CFLAGS) tanh.cpp	

max_pooling.o: max_pooling.cpp
	$(CC) $(CFLAGS) max_pooling.cpp

avg_pooling.o: avg_pooling.cpp
	$(CC) $(CFLAGS) avg_pooling.cpp	

sigmoid.o: sigmoid.cpp
	$(CC) $(CFLAGS) sigmoid.cpp

softmax.o: softmax.cpp
	$(CC) $(CFLAGS) softmax.cpp

clean: 
	rm -rf *o library			 
