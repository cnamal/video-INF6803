//
// Created by namalgac on 3/12/16.
//

#include "PFMS.h"
#include <opencv2/highgui/highgui.hpp>
#include "stdlib.h"

PFMS::PFMS(VideoAbstract &video, AbstractFrameTransformation &trans,std::string windowName,int waitDelay) : TrackingMethod(video,trans,windowName,waitDelay),MeanShift(video,trans,windowName,waitDelay,false),ParticleFilter(video,trans,windowName,waitDelay,false)
{
    MeanShift::process();
    rectangle(frame, modelArea, cv::Scalar(0, 0, 255));
    cv::imshow(windowName,frame);
    cv::waitKey(waitDelay);
}

void PFMS::process()
{
    ParticleFilter::process();
    MeanShift::process();
}