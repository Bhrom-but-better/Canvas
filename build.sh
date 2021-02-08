#!/bin/sh
g++ -std=c++17 -c src/*.cpp
g++ -std=c++17 -c Source.cpp
g++ *.o -o Program -lsfml-graphics -lsfml-window -lsfml-system
