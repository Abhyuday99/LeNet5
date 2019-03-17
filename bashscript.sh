#!/bin/bash

g++ $(pkg-config --cflags --libs /usr/local/Cellar/opencv/4.0.1/lib/pkgconfig/opencv4.pc) -std=c++11 read_image.cpp -o read_image

./read_image 2.png

#g++ -o Layer1 Layer1.cpp ${MKLROOT}/lib/libmkl_intel_ilp64.a ${MKLROOT}/lib/libmkl_sequential.a ${MKLROOT}/lib/libmkl_core.a -lpthread -lm -ldl  -DMKL_ILP64 -m64 -I${MKLROOT}/include
#
#./Layer1
#
#g++ -o Layer2 Layer2.cpp
#
#./Layer2
#
#g++ -o Layer3 Layer3.cpp ${MKLROOT}/lib/libmkl_intel_ilp64.a ${MKLROOT}/lib/libmkl_sequential.a ${MKLROOT}/lib/libmkl_core.a -lpthread -lm -ldl  -DMKL_ILP64 -m64 -I${MKLROOT}/include
#
#./Layer3
#
#g++ -o Layer4 Layer4.cpp
#
#./Layer4
#
#g++ -o Layer5 Layer5.cpp ${MKLROOT}/lib/libmkl_intel_ilp64.a ${MKLROOT}/lib/libmkl_sequential.a ${MKLROOT}/lib/libmkl_core.a -lpthread -lm -ldl  -DMKL_ILP64 -m64 -I${MKLROOT}/include
#
#./Layer5
#
#g++ -o Layer6 Layer6.cpp ${MKLROOT}/lib/libmkl_intel_ilp64.a ${MKLROOT}/lib/libmkl_sequential.a ${MKLROOT}/lib/libmkl_core.a -lpthread -lm -ldl  -DMKL_ILP64 -m64 -I${MKLROOT}/include
#
#./Layer6
#
#g++ -o softmax_prob softmax_prob.cpp
#
#./softmax_prob
#
#g++ -o top5_softmax_probablity top5_softmax_probablity.cpp
#
#./top5_softmax_probablity
