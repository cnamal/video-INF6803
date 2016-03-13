//
// Created by namalgac on 3/12/16.
//

#ifndef TP2_JPSEQUENCE_H
#define TP2_JPSEQUENCE_H

#include "VideoAbstract.h"
#include <opencv2/highgui/highgui.hpp>

#define PATH "jp1/jp1_sequence/"
#define FILEPATH PATH "%04d.jpg"
class JPSequence : public VideoAbstract{

public:
    JPSequence();
    ~JPSequence();
    cv::Rect getModelArea();
    cv::Mat getFrame();
    virtual bool hasFrame();

private:
    char filename[30];
    int counter=1;
    int endCounter=609;
};


#endif //TP2_JPSEQUENCE_H
