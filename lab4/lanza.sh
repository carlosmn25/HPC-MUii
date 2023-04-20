#!/bin/bash
# Lanza el programa de la práctica 4

for i in range{1..10}; do
    mpirun -n 1 -H nodo51 --mca btl tcp,self ./lab4.o 4 1
    mpirun -n 1 -H nodo51 --mca btl tcp,self ./lab4.o 4 2
    mpirun -n 1 -H nodo51 --mca btl tcp,self ./lab4.o 4 4

    mpirun -n 2 -H nodo51,nodo52 --mca btl tcp,self ./lab4.o 4 1
    mpirun -n 2 -H nodo51,nodo52 --mca btl tcp,self ./lab4.o 4 2
    mpirun -n 2 -H nodo51,nodo52 --mca btl tcp,self ./lab4.o 4 4

    mpirun -n 4 -H nodo51,nodo52,nodo53,nodo54 --mca btl tcp,self ./lab4.o 4 1
    mpirun -n 4 -H nodo51,nodo52,nodo53,nodo54 --mca btl tcp,self ./lab4.o 4 2
    mpirun -n 4 -H nodo51,nodo52,nodo53,nodo54 --mca btl tcp,self ./lab4.o 4 4

    mpirun -n 8 -H nodo51,nodo52,nodo53,nodo54,nodo55,nodo56,nodo57,nodo58 --mca btl tcp,self ./lab4.o 4 1
    mpirun -n 8 -H nodo51,nodo52,nodo53,nodo54,nodo55,nodo56,nodo57,nodo58 --mca btl tcp,self ./lab4.o 4 2
    mpirun -n 8 -H nodo51,nodo52,nodo53,nodo54,nodo55,nodo56,nodo57,nodo58 --mca btl tcp,self ./lab4.o 4 4
done
