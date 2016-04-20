CC=g++
EXE=main
CPPFLAGS=-std=c++11 `pkg-config --cflags opencv`
LDLIBS=`pkg-config --libs opencv`

.PHONY: all clean

all: $(EXE)
	
main : Eigenfaces.o Eigenfaces.h

clean:
	rm -rf $(EXE) *.o
