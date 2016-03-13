//
// Created by namalgac on 3/12/16.
//

#ifndef TP2_FOLLOWVISIBLEFACE_H
#define TP2_FOLLOWVISIBLEFACE_H

#include "VideoAbstract.h"
#include <opencv2/highgui/highgui.hpp>

#define FILENAME "suivi_visage_visible.avi"

class FollowVisibleFace : public VideoAbstract {

public:
    FollowVisibleFace();
    ~FollowVisibleFace();
    cv::Rect getModelArea();
    cv::Mat getFrame();
    virtual bool hasFrame();

private:
    cv::VideoCapture cap;
};


#endif //TP2_FOLLOWVISIBLEFACE_H
