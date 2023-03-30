#!/bin/bash

gcc -fopenmp lab3_automatizar.c -o lab3.o

for j in {1..10}
do
    # Do a for loop from 1 to 20
    for i in {1..20}
    do
        # Launch the program with 4 million iterations and the current value of i+1
        ./lab3.o 4000000 $i
    done
done