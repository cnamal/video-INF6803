//
// Created by namalgac on 3/12/16.
//

#ifndef TP2_GRAYFRAMETRANSFORMATION_H
#define TP2_GRAYFRAMETRANSFORMATION_H

#include "AbstractFrameTransformation.h"

class GrayFrameTransformation : public AbstractFrameTransformation{

public:
    GrayFrameTransformation();
    cv::Mat getTransformedFrame(cv::Mat frame);
};


#endif //TP2_GRAYFRAMETRANSFORMATION_H
