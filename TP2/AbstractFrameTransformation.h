//
// Created by namalgac on 3/12/16.
//

#ifndef TP2_ABSTRACTFRAMETRANSFORMATION_H
#define TP2_ABSTRACTFRAMETRANSFORMATION_H

#include <opencv/cv.h>

class AbstractFrameTransformation {

public:
    virtual cv::Mat getTransformedFrame(cv::Mat frame)=0;
    virtual int getHistSize(){ return histSize;};
    virtual int* getChannels(){ return {0};};
    float* getRange() { return range;};

protected:
    int histSize;
    float range[2];
};


#endif //TP2_ABSTRACTFRAMETRANSFORMATION_H
