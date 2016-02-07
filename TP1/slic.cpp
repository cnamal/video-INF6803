#include "slic.h"
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include "pixel.h"
#include "center.h"

using namespace cv;

Slic::Slic(Mat &imageRGB,long K,int nb_it,int m):imageRGB(imageRGB),K(K),nb_it(nb_it),m(m)
{
    cvtColor(imageRGB,image,CV_BGR2Lab);
}

void Slic::superpixels()
{
    Mat grey;
    cvtColor(image,grey,CV_BGR2GRAY);
    Mat grad;
    Sobel(grey,grad,grey.depth(),1,1,3,1,0,BORDER_DEFAULT);
    long N = image.total();
    long S=sqrt(N/K);
    vector<Center> centers;
    for(int i=S;i<image.cols-S/2;i+=S){
        for(int j=S;j<image.rows-S/2;j+=S){
            CvPoint point;
            lowestGradient(j,i,grad,&point);
            Vec3b lab = image.at<Vec3b>(point.y,point.x);
            Center c(lab.val[0],lab.val[1],lab.val[2],point.x,point.y);
            centers.push_back(c);
        }
    }

   
    vector<vector<Pixel> > pixels(image.cols,vector<Pixel>(image.rows,Pixel(-1,INT_MAX)));

    for(int iteration =0; iteration<nb_it;iteration++){

        if(iteration)
            for(int i=0;i<image.cols;i++)
                for(int j=0;j< image.rows;j++)
                    pixels[i][j].d=INT_MAX;


        for (int index=0; index< centers.size();index++){
            Center it = centers[index];
            for(int i=it.x-S;i<it.x+S;i++){
                for(int j=it.y-S;j<it.y+S;j++){
                    if(i>=0 && i< image.cols && j>=0 && j<image.rows){
                        Vec3b vec = image.at<Vec3b>(j,i);
                        double dc = sqrt(pow(vec.val[0]-it.l,2)+pow(vec.val[1]-it.a,2)+pow(vec.val[2]-it.b,2));
                        double ds = sqrt(pow(it.x-i,2)+pow(it.y-j,2));
                        double D = sqrt(pow(dc/m,2)+pow(ds/S,2));
                        if(D < pixels[i][j].d){
                            pixels[i][j].d=D;
                            pixels[i][j].l = index;
                        }
                    }
                }
            }
        }

        vector<int> nb_pixels(centers.size(),0);
        for(int i=0; i<centers.size();i++){
            centers[i].x=0;
            centers[i].y=0;
            centers[i].l=0;
            centers[i].a=0;
            centers[i].b=0;
        }


        for (int i=0;i<image.cols;i++){
            for (int j=0;j<image.rows;j++){
                int label = pixels[i][j].l;
                if(label>=0){
                    Vec3b vec = image.at<Vec3b>(j,i);
                    Center center = centers[label];
                    center.x+=i;
                    center.y+=j;
                    center.l+=vec.val[0];
                    center.a+=vec.val[1];
                    center.b+=vec.val[2];
                    centers[label]=center;
                    nb_pixels[label]++;
                }

            }
        }

        for(int  i=0; i< centers.size();i++){
            centers[i].x/=nb_pixels[i];
            centers[i].y/=nb_pixels[i];
            centers[i].l/=nb_pixels[i];
            centers[i].a/=nb_pixels[i];
            centers[i].b/=nb_pixels[i];
        }
    }

    vector<CvPoint> border;
    vector<vector<bool> > occupied(image.rows,vector<bool>(image.cols,false));

    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            int diff = 0;
            int row_min = i -1 <0?i:i-1;
            int row_max = i+1 <image.rows?i+1:i;
            int col_min = j-1<0?j:j-1;
            int col_max = j+1<image.cols?j+1:j;

            for(int k=row_min;k<=row_max;k++)
                for(int l=col_min; l<=col_max;l++)
                    if(!occupied[k][l] && pixels[i][j].l != pixels[k][l].l)
                        diff++;

            if (diff >= 2) {
                border.push_back(cvPoint(i,j));
                occupied[i][j] = true;
            }
        }
    }

    for (int i = 0; i < border.size(); i++) {
        Vec3b im = imageRGB.at<Vec3b>(border[i].y,border[i].x);
        im.val[0]=255;
        im.val[1]=0;
        im.val[2]=0;
        imageRGB.at<Vec3b>(border[i].y,border[i].x)=im;
    }

    imshow("Image",imageRGB);
    waitKey(0);
}

void Slic::lowestGradient(int row,int col,Mat const &image, CvPoint *point){
    int min = INT_MAX;
    for(int i=col-1;i<=col+1;i++){
        for(int j=row-1;j<=row+1;j++){
            if(image.at<uchar>(j,i)<min){
                point->x=i;
                point->y=j;
                min = image.at<uchar>(j,i);
            }
        }
    }
}
