//
// Created by namalgac on 3/12/16.
//

#ifndef TP2_MEANSHIFT_H
#define TP2_MEANSHIFT_H

#include <opencv/cv.h>
#include "TrackingMethod.h"

class MeanShift : virtual public TrackingMethod {

public:
    MeanShift(VideoAbstract& video,AbstractFrameTransformation& trans,std::string windowName="Video",int waitDelay = 33,bool show = true);

protected:
    void process();
    void replace(cv::Mat frame, cv::Mat hist);
    cv::Point center(cv::Mat frame, cv::Rect roi);
    cv::Point centerPoint;
    cv::Point prev;
};


#endif //TP2_MEANSHIFT_H
