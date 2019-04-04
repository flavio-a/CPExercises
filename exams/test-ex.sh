#!/bin/bash

PROGRAMNAME=$1
NUMBERTEST=$2
g++ -std=c++11 -O3 -o $PROGRAMNAME.out $PROGRAMNAME.cpp
for i in $(seq 0 $NUMBERTEST); do
	echo "test #"$i
	./$PROGRAMNAME.out < ${PROGRAMNAME}_tests/input${i}.txt | diff ${PROGRAMNAME}_tests/output${i}.txt -
done
