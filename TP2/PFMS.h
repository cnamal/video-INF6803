//
// Created by namalgac on 3/12/16.
//

#ifndef TP2_PFMS_H
#define TP2_PFMS_H

#include "ParticleFilter.h"
#include "MeanShift.h"
#include "VideoAbstract.h"
#include "AbstractFrameTransformation.h"
#include <string>

class PFMS : public MeanShift,public ParticleFilter{

public:
    PFMS(VideoAbstract& video,AbstractFrameTransformation& trans,std::string windowName);

protected:
    virtual void process();

};


#endif //TP2_PFMS_H
