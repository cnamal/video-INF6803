//
// Created by namalgac on 3/12/16.
//

#include "FollowVisibleFace.h"
#include <stdlib.h>

using namespace cv;

FollowVisibleFace::FollowVisibleFace(): cap(FILENAME)
{

    if (!cap.read(frame)){
        std::cerr << "Error, couldn't read the video at " << FILENAME<< std::endl;
        exit(1);
    }
    hasNextFrame=true;
}

FollowVisibleFace::~FollowVisibleFace()
{
    cap.release();
}

Rect FollowVisibleFace::getModelArea(){
    return Rect(273,115,60,60);
}

Mat FollowVisibleFace::getFrame(){
    return frame;
}

bool FollowVisibleFace::hasFrame() {
    return cap.read(frame);
}