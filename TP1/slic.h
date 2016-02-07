#ifndef SLIC_H
#define SLIC_H
#include <opencv2/core/core.hpp>
#include <opencv/cv.h>

class Slic {
    public:
        Slic(cv::Mat &image,long K=1200, int nb_it=10,int m=35);
        void superpixels();
    private:
        cv::Mat imageRGB;
        cv::Mat image;
        long K;
        int nb_it;
        int m;
        void lowestGradient(int row,int col,cv::Mat const &image, CvPoint *point);
};
#endif
