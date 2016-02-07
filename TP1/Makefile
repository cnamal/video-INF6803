CC=g++
EXE=part1 part2
CPPFLAGS=-std=c++11 `pkg-config --cflags opencv`
LDLIBS=`pkg-config --libs opencv`

.PHONY: all clean

all: part1 part2
	
part2: center.h pixel.h slic.h slic.cpp
clean:
	rm -rf part1 part2
