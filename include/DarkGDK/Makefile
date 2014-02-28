#!/bin/bash

# DarkGDK
# =======
# 
# DarkGDK is a Win/Linux/MacOS game development kit providing hundreds of useful command to create games and interactive 3d media
# 
# make starbench


libDarkGDK.o:
	g++ -Wall -O3 -o libDarkGDK.o source/libDarkGDK/DarkGDK.cpp

example_1:	starbench.o libDarkGDK.o
	g++ -s -o starbench starbench.o -lm -lDarkGDK -lIrrlicht -lX11 -lXxf86vm -lGL -lXCursor

starbench.o:
	g++ -Wall -O3 -o starbench.o examples/StarBench.cpp
