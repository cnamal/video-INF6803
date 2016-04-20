//
// Created by namalgac on 4/8/16.
//

#ifndef TP3_EIGENFACES_H
#define TP3_EIGENFACES_H

#include <vector>

#include "opencv2/opencv.hpp"

class Eigenfaces {

public:
    Eigenfaces(std::vector<cv::Mat> images, std::vector<int> labels,int MP,int threshold);
    int predict(const cv::Mat& src);

private:
    void compute( std::vector<cv::Mat> srcImages, std::vector<int> labels) ;
    cv::Mat asRowMatrix(std::vector<cv::Mat> images);
    cv::Mat project(const cv::Mat& src);
    int MP;
    cv::Mat mean;
    std::vector<cv::Mat> projections;
    cv::Mat eigenfaces;
    std::vector<int> _labels;
    void substract(cv::Mat gammas);
    int threshold;
};


#endif //TP3_EIGENFACES_H
