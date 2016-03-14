//
// Created by namalgac on 3/12/16.
//

#include "MeanShift.h"
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>

using namespace cv;


void MeanShift::replace(Mat frame, Mat hist) {
    for (int i = 0; i < frame.rows; i++) {
        for (int j = 0; j < frame.cols; j++) {
            uchar value = frame.at<uchar>(i, j);
            int proba = cvRound(hist.at<float>(value)*(trans.getHistSize()-1)/max);
            if(proba>(trans.getHistSize()-1))
                proba=(trans.getHistSize()-1);
            frame.at<uchar>(i, j) = proba;
        }
    }
}

Point MeanShift::center(Mat frame, Rect roi) {
    int m00 = 0;
    int x = 0;
    int y = 0;
    for (int i = roi.y; i < roi.height + roi.y; i++) {
        for (int j = roi.x; j < roi.width + roi.x; j++) {
            m00 += frame.at<uchar>(i, j);
            x += j * frame.at<uchar>(i, j);
            y += i * frame.at<uchar>(i, j);
        }
    }
    Point point(x / m00, y / m00);
    point.x = x / m00;
    point.y = y / m00;
    return point;
}

void MeanShift::process() {
    replace(transformedFrame, histRef);
    do {
        prev.x = centerPoint.x;
        prev.y = centerPoint.y;
        Mat ROI = transformedFrame(modelArea);
        centerPoint = center(transformedFrame, modelArea);
        modelArea.x = centerPoint.x - modelArea.width / 2;
        modelArea.x = modelArea.x < 0 ? 0 : modelArea.x >= frame.cols ? frame.cols - 1 : modelArea.x;
        modelArea.y = centerPoint.y - modelArea.height / 2;
        modelArea.y = modelArea.y < 0 ? 0 : modelArea.y >= frame.rows ? frame.rows - 1 : modelArea.y;
    } while (prev.x != centerPoint.x || prev.y != centerPoint.y);
}

MeanShift::MeanShift(VideoAbstract &video, AbstractFrameTransformation &trans,string windowName,int waitDelay,bool show) : TrackingMethod(video, trans, windowName,waitDelay) {
    if(show){
        rectangle(frame, modelArea, Scalar(0, 0, 255));
        imshow(windowName, frame);
        waitKey(waitDelay);
    }
}