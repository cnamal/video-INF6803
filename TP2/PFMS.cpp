//
// Created by namalgac on 3/12/16.
//

#include "PFMS.h"
#include <opencv2/highgui/highgui.hpp>
#include "stdlib.h"

PFMS::PFMS(VideoAbstract &video, AbstractFrameTransformation &trans,std::string windowName) : MeanShift(video,trans,windowName,false),ParticleFilter(video,trans,windowName,false),TrackingMethod(video,trans,windowName)
{
    MeanShift::process();
    cv::waitKey(0);
}

void PFMS::process()
{
    ParticleFilter::process();
    MeanShift::process();
}