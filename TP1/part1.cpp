#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <iostream>

#define IMAGE 0

using namespace std;
using namespace cv;


int main(){

#if IMAGE
	Mat image;
	image=imread("lena.jpg",CV_LOAD_IMAGE_COLOR);
	if(!image.data){
		cout <<  "Could not open or find the image" << std::endl ;
		return -1;
	}
	Mat channel[3];
	split(image, channel);
	channel[1]=Mat::zeros(image.rows, image.cols, CV_8UC1);
	channel[2]=Mat::zeros(image.rows, image.cols, CV_8UC1);
	merge(channel,3,image);
	cvtColor(image,image,CV_RGB2GRAY);
	imshow("nameWin", image);
#else
	VideoCapture cap("video1.avi");
	cap.set(CV_CAP_PROP_FPS,30);
	int waitKeyValue = 1;
	Mat frame;
	while (1) {
		if (!cap.read(frame)) break;
		imshow("Video1",frame);
		int key = cv::waitKey(33);
	}
	cap.release();
#endif
	waitKey(0);
	return 0;
}
