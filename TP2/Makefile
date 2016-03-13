CC=g++
EXE=p1 p2 p3 main
CPPFLAGS=-std=c++11 `pkg-config --cflags opencv`
LDLIBS=`pkg-config --libs opencv`

.PHONY: all clean

all: $(EXE)
	
main : FollowVisibleFace.o FollowVisibleFace.h TrackingMethod.o TrackingMethod.h MeanShift.h MeanShift.o HSVFrameTransformation.h HSVFrameTransformation.o GrayFrameTransformation.h GrayFrameTransformation.o ParticleFilter.o ParticleFilter.h PFMS.o PFMS.h JPSequence.h JPSequence.o

clean:
	rm -rf $(EXE) *.o
