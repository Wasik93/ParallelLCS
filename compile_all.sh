#!/bin/sh

g++ Generator.cpp -o GENERATOR

g++ NEON.cpp -o NEON

g++ -std=c++14 -fopenmp -O3 OpenMP.cpp -o OMP

g++ -std=c++14 -pthread -O3 Threads.cpp -o THREADS

./GENERATOR > test.txt


