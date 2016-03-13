//
// Created by namalgac on 3/12/16.
//

#include "JPSequence.h"

using namespace cv;
using namespace std;

JPSequence::JPSequence()
{

    sprintf(filename,FILEPATH,counter);
    frame=imread(filename,CV_LOAD_IMAGE_COLOR);
    if(!frame.data){
        cerr << "Error, couldn't read " << filename << endl;
        cerr << "Make sure the path to the jp sequence is " << PATH << endl;
        exit(1);
    }
    hasNextFrame=true;
}

JPSequence::~JPSequence()
{
}

Rect JPSequence::getModelArea(){
    return Rect(165,140,50,50);
}

Mat JPSequence::getFrame(){
    sprintf(filename,FILEPATH,counter);
    frame=imread(filename,CV_LOAD_IMAGE_COLOR);
    if(!frame.data){
        cerr << "Error, couldn't read " << filename << endl;
        cerr << "Make sure the path to the jp sequence is " << PATH << endl;
        exit(1);
    }

    return frame;
}

bool JPSequence::hasFrame() {
    return ++counter != endCounter;
}