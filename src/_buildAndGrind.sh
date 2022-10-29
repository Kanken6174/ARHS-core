#!/bin/bash
clear; 
rm ./callgrind.out.*; 
cmake --build . -j5; 
valgrind --tool=callgrind ./prog; 
kcachegrind callgrind.out.*