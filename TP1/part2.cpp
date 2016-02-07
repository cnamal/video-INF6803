#include <iostream>
#include <vector>
#include <utility>
#include "center.h"
#include "pixel.h"
#include "slic.h"
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;

int main(int argc, char *argv[]){

    Mat imageRGB;
    string file =argc==1?"lena.jpg" : argv[1];
    if(argc==1)
        cerr << "No filename given. Testing default lena.jpg" << endl;
    imageRGB=imread(file,CV_LOAD_IMAGE_COLOR);

    if(!imageRGB.data){
        cout <<  "Could not open or find the image "<< file  << std::endl ;
        return -1;
    }

    Slic s(imageRGB);
    s.superpixels();
    return 0;
}
