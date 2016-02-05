#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <iostream>
#include <vector>
#include <utility>
#include <climits>

#define IMAGE 0

using namespace std;
using namespace cv;


pair<int,int> lowestGradient(int row,int col,Mat const &image){
	int rowMin = row-1<0?row:row-1;
	int rowMax = row+1>image.rows?row:row+1;
	int colMin = col-1<0?col:col-1;
	int colMax = col+1>image.cols?col:col+1;
	pair<int,int> res;
	int min=INT_MAX;
	for(int i=rowMin;i<=rowMax;i++){
		for (int j=colMin;j<=colMax;j++){
			if(
		}
	}
}

int main(){


	Mat image;
	image=imread("lena.jpg",CV_LOAD_IMAGE_COLOR);
	if(!image.data){
		cout <<  "Could not open or find the image" << std::endl ;
		return -1;
	}
	cvtColor(image,image,CV_BGR2Lab);
	long N = image.total();
	long K=1200;
	long S=sqrt(N/K);
	vector<Mat> centers;
	for(int i=0;i<image.rows/S;i++){
		for(int j=0;j<image.cols/S;j++){
			centers.push_back(image.at<Mat>(i,j));
		}
	}
	return 0;
}
