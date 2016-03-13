//
// Created by namalgac on 3/12/16.
//

#include "HSVFrameTransformation.h"

using namespace cv;

Mat HSVFrameTransformation::getTransformedFrame(Mat frame)
{
    Mat tmp;
    cvtColor(frame, tmp,CV_BGR2HSV);
    vector<Mat> planes;
    split(tmp,planes);
    return planes[0];
}

HSVFrameTransformation::HSVFrameTransformation()
{
    range[0] = 0;
    range[1] = 180;
    histSize = 180;
}

