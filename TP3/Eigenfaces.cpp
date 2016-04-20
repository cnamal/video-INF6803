//
// Created by namalgac on 4/8/16.
//

#include "Eigenfaces.h"

using namespace std;
using namespace cv;

Eigenfaces::Eigenfaces(vector<Mat> images, vector<int> labels,int MP,int threshold):MP(MP),threshold(threshold)
{
    compute(images,labels);
}

void Eigenfaces::compute( vector<Mat> srcImages, vector<int> labels) {

    Mat gammas = asRowMatrix(srcImages);
    int M = gammas.rows;


    if((MP <= 0) || (MP > M))
        MP = M;


    reduce(gammas,mean,0,CV_REDUCE_AVG);
    substract(gammas);
    Mat eigenvalues;
    Mat eigenvectors;
    eigen(gammas*gammas.t(),eigenvalues,eigenvectors);

    eigenvectors = gammas.t()*eigenvectors.t();
    eigenfaces = eigenvectors(cv::Rect(0,0,MP,eigenvectors.rows));
    for(int i=0;i<eigenfaces.cols ;i++)
        normalize(eigenfaces.col(i),eigenfaces.col(i));


    _labels = labels;
    for(int i = 0; i < gammas.rows; i++) {
        Mat p = project(gammas.row(i).clone());
        this->projections.push_back(p);
    }
}

void Eigenfaces::substract(Mat gammas){
    for(int i =0 ; i<gammas.rows;i++){
        Mat r_i = gammas.row(i);
        subtract(r_i, mean, r_i);
    }
}

Mat Eigenfaces::asRowMatrix(vector<Mat> src) {
    size_t M = src.size();
    size_t N2 = src[0].total();
    Mat data(M, N2, CV_64FC1);
    for(int i = 0; i < M; i++) {
        // destination row
        Mat xi = data.row(i);
        // if not continuous, we have to clone first
        if(src[i].isContinuous())
            src[i].reshape(1, 1).convertTo(xi, CV_64FC1);
        else
            src[i].clone().reshape(1, 1).convertTo(xi, CV_64FC1);

    }
    return data;
}

Mat Eigenfaces::project(const Mat& src) {

    Mat X, Y;
    // need to convert, if not throws an error
    src.convertTo(X, eigenfaces.type());

    Y = X*eigenfaces;
    return Y;
}

int Eigenfaces::predict(const Mat& src) {
    Mat gamma ;
    // need to convert, if not throws an error
    src.convertTo(gamma,mean.type());
    gamma = gamma.reshape(1,1);
    gamma= gamma-mean;
    Mat q = project(gamma);
    double min = DBL_MAX;
    int label = -1;
    for(int i = 0; i < projections.size(); i++) {
        double dist = norm(projections[i], q, NORM_L2);
        if(dist < min) {
            min = dist;
            label = _labels[i];
        }
    }
    //cout << min << " " << max << endl;
    if(min>threshold) {
        Mat omegaP;
        omegaP = q.at<double>(0,0) * eigenfaces.col(0);
        for (int i = 1; i < q.cols; i++) {
            omegaP += q.at<double>(0,i) * eigenfaces.col(i);
        }

        double dist = norm(gamma.t(), omegaP, NORM_L2);
        //cout << "dist " << dist << endl;
        if(dist>threshold){
            //cout << "Unknown" << endl;
            return -1;
        }else{
            //cout << "New face" << endl;
            return -2;
        }
    }
    return label;
}



