//
// Created by namalgac on 3/12/16.
//

#ifndef TP2_HSVFRAMETRANSFORMATION_H
#define TP2_HSVFRAMETRANSFORMATION_H

#include "AbstractFrameTransformation.h"

class HSVFrameTransformation : public AbstractFrameTransformation{

public:
    HSVFrameTransformation();
    cv::Mat getTransformedFrame(cv::Mat frame);

};


#endif //TP2_HSVFRAMETRANSFORMATION_H
