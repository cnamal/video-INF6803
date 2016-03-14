//
// Created by namalgac on 3/12/16.
//

#ifndef TP2_TRACKINGMETHOD_H
#define TP2_TRACKINGMETHOD_H

#include "VideoAbstract.h"
#include "AbstractFrameTransformation.h"
#include <string>

class TrackingMethod {

public:
    TrackingMethod(VideoAbstract& video,AbstractFrameTransformation& trans,std::string windowName = "Video",int waitDelay = 33);
    void track();
    
protected:
    virtual void process()=0;
    void getHistROI(cv::Mat& hist,cv::Mat* ROI);
    VideoAbstract& video;
    AbstractFrameTransformation& trans;
    cv::Mat frame;
    cv::Mat transformedFrame;
    cv::Rect modelArea;
    cv::Mat histRef;
    cv::Size fSize;
    const float* range;
    int histSize;
    double max;
    std::string windowName;
    int waitDelay;
};


#endif //TP2_TRACKINGMETHOD_H
