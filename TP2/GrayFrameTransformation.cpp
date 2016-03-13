//
// Created by namalgac on 3/12/16.
//

#include "GrayFrameTransformation.h"

using namespace cv;

Mat GrayFrameTransformation::getTransformedFrame(Mat frame)
{
    Mat tmp;
    cvtColor(frame, tmp,CV_BGR2GRAY);
    return tmp;
}

GrayFrameTransformation::GrayFrameTransformation()
{
    range[0] = 0;
    range[1] = 256;
    histSize = 256;
}


