//
// Created by namalgac on 3/12/16.
//

#include "TrackingMethod.h"
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

TrackingMethod::TrackingMethod(VideoAbstract& video,AbstractFrameTransformation& trans,string windowName): video(video),trans(trans),windowName(windowName)
{
    frame = video.getFrame();
    fSize = frame.size();
    modelArea = video.getModelArea();
    transformedFrame = trans.getTransformedFrame(frame);
    Mat ROI = transformedFrame(modelArea);
    range= {trans.getRange()};
    histSize = trans.getHistSize();
    getHistROI(histRef,&ROI);
    namedWindow(windowName);
}

void TrackingMethod::getHistROI(cv::Mat& hist,Mat* ROI)
{
    calcHist(ROI,1,trans.getChannels(),Mat(),hist,1,&histSize,&range);
}

void TrackingMethod::track()
{
    while(video.hasFrame()){
        frame = video.getFrame();
        transformedFrame = trans.getTransformedFrame(frame);
        process();
        rectangle(frame,modelArea,Scalar(0,0,255));
        imshow(windowName,frame);
        waitKey(0);
    }
}
