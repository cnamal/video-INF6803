//
// Created by namalgac on 3/12/16.
//

#include "ParticleFilter.h"
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

ParticleFilter::ParticleFilter(VideoAbstract &video, AbstractFrameTransformation &trans,string windowName,bool show) : TrackingMethod(video,
                                                                                                          trans,windowName) {
    //cerr<< "beg"<< endl;
    srand(200);
    /*frame = video.getFrame();
    modelArea = video.getModelArea();
    transformedFrame = trans.getTransformedFrame(frame);
    comparator([](const std::pair<double, cv::Rect>& firstElem, const std::pair<double, cv::Rect>& secondElem){ return true;});
    Mat ROI = transformedFrame(modelArea);
    const float* range= {trans.getRange()};
    int histSize = trans.getHistSize();
    calcHist(&ROI,1,trans.getChannels(),Mat(),histRef,1,&histSize,&range);*/
    /*for(int i=0;i<nbParticles;i++){
        ROI = transformedFrame(listR[i]);
        Mat hist;
        calcHist(&ROI,1,trans.getChannels(),Mat(),hist,1,&histSize,&range);
        listPair.push_back(make_pair(histComp(histRef, hist),listR[i]));
    }
    sort(listPair.begin(),listPair.end(),comparator);*/
    //cerr << modelArea<< " " << nbParticles<< endl;
    //cout << histRef<< endl;
    listR = particle(modelArea, nbParticles);
    computeParticles();
    //cerr << "end"<< endl;
    if(show){
        rectangle(frame,listPair[0].second,Scalar(0, 0, 255));
        imshow(windowName, frame);
        waitKey(0);
    } else
        cerr << "didn't show " << endl;
}

double ParticleFilter::histComp(Mat h1, Mat h2) {

    return compareHist(h1, h2, CV_COMP_BHATTACHARYYA);
}

void ParticleFilter::process() {
    cerr << "particle process "<< endl;
    listR.clear();
    for (int i = 0; i < 10; i++) {
        vector<Rect> tmp = particle(listPair[i].second, 100);
        listR.insert(listR.end(), tmp.begin(), tmp.end());
    }
    listPair.clear();
    computeParticles();
}

vector<Rect> ParticleFilter::particle(Rect primary, int nb) {
    vector<Rect> list;
    for (int i = 0; i < nb; i++) {
        Rect p;
        int tempX = 0;
        int tempY = 0;
        int tempC = 0;
        double tempR = 0;


        tempR = (double) ((rand() % 10) + 1) / 10;
        tempX = primary.x + (int) (primary.width * tempR);

        tempR = (double) ((rand() % 10) + 1) / 10;
        tempY = primary.y + (int) (primary.height * tempR);

        tempR = ((double) ((rand() % 10) + 1) / 10); // a revoir
        tempC = primary.width + (int) (primary.width / 3 * (tempR - 0.5));
        if (tempX + tempC >= fSize.width)
            tempC = (fSize.width - tempX) - 1;
        if (tempX - tempC <= 0)
            tempC = tempX + 1;
        if (tempY + tempC >= fSize.height)
            tempC = (fSize.height - tempY) - 1;
        if (tempY - tempC <= 0)
            tempC = tempY + 1;

        p.x = tempX - tempC / 2;
        p.y = tempY - tempC / 2;
        p.width = tempC;
        p.height = tempC;
        list.push_back(p);
        /*cout << "Center (" << tempX << ", " << tempY << ")" << endl;
        cout << "Top-Left (" << p.x << ", " << p.y << ")" << endl;
        cout << "Width-Height (" << p.width << ", " << p.height << ")" << endl;*/
    }

    return list;
}

void ParticleFilter::computeParticles() {
    for (int i = 0; i < nbParticles; i++) {
        Mat ROI = transformedFrame(listR[i]);
        Mat hist;
        /*calcHist(&ROI,1,trans.getChannels(),Mat(),hist,1,&histSize,&range);*/
        getHistROI(hist, &ROI);
        listPair.push_back(make_pair(histComp(histRef, hist), listR[i]));
    }

    sort(listPair.begin(), listPair.end(),
         [](const pair<double, Rect> &firstElem, const pair<double, Rect> &secondElem) {
             return firstElem.first < secondElem.first;

         });

    modelArea = listPair[0].second;
}