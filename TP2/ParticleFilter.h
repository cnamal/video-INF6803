//
// Created by namalgac on 3/12/16.
//

#ifndef TP2_PARTICLEFILTER_H
#define TP2_PARTICLEFILTER_H


#include <opencv/cv.h>
#include "TrackingMethod.h"
#include <vector>
#include <utility>
#include <functional>

class ParticleFilter : virtual public TrackingMethod{

public:
    ParticleFilter(VideoAbstract& video,AbstractFrameTransformation& trans,std::string windowName,bool show =true);

protected:
    void process();
    double histComp(cv::Mat h1, cv::Mat h2);
    std::vector<cv::Rect> particle(cv::Rect primary,int nb);
    std::vector<std::pair<double,cv::Rect>> listPair;
    std::vector<cv::Rect> listR;
    const int nbParticles =1000;
    void computeParticles();
};


#endif //TP2_PARTICLEFILTER_H
