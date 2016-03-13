//
// Created by namalgac on 3/12/16.
//

#ifndef TP2_VIDEOABSTRACT_H
#define TP2_VIDEOABSTRACT_H

#include <opencv/cv.h>

class VideoAbstract {

public:
    virtual cv::Rect getModelArea()=0;
    virtual cv::Mat getFrame()=0;
    virtual bool hasFrame()=0;

protected:
    cv::Mat frame;
    bool hasNextFrame;
};


#endif //TP2_VIDEOABSTRACT_H
