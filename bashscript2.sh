#!/bin/bash

./read_image $1
./Layer1
./Layer2
./Layer3
./Layer4
./Layer5
./Layer6
./softmax_prob
./top5_softmax_probablity
