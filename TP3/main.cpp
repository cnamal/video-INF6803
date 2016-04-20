#include <iostream>

#include "Eigenfaces.h"

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
using namespace std;
using namespace cv;

void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels) {
    ifstream file(filename.c_str(), ifstream::in);
    if(!file)
        throw exception();
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);

        getline(liness, path, ';');
        getline(liness, classlabel);
        Mat tmp = imread(path,0); // 0 for greyscale
        if(!tmp.data){
            cerr << "Impossible to read image " << path <<endl;
            exit(1);
        }

        images.push_back(tmp);
        labels.push_back(atoi(classlabel.c_str()));
    }
}

int main(int argc, char *argv[]) {
    vector<Mat> images;
    vector<int> labels;
    vector<Mat> training;
    vector<int> trainingLabels;
    if(argc != 4 && argc !=5) {
        cout << "usage: " << argv[0] << " <csv> num_eigenfaces threshold [<test>]" << endl;
        cout << "csv : file with path and labels" <<endl;
        cout << "\t format : path;label" << endl;
        cout << "\t label should be -1 for unknown (not a face) and -2 for a new face" << endl;
        cout << "\t half of the images will be used for training and the other half for testing" << endl;
        cout << "num_eigenfaces : number of eigenfaces. (M' in the paper)" << endl;
        cout << "threshold : threshold for unknown images and new faces" << endl;
        cout << "test (optional) : additional test batch" << endl;
        exit(1);
    }

    string csv = string(argv[1]);
    try {
        read_csv(csv, images, labels);
    } catch(exception& e) {
        cerr << "Error opening file \"" << csv << "\"." << endl;
        exit(1);
    }
    long size = images.size()/2;
    srand(time(0));
    for(long i=0;i<size;i++) {
        long random_variable = (rand() % images.size());
        training.push_back(images[random_variable]);
        trainingLabels.push_back(labels[random_variable]);
        images.erase(images.begin() + random_variable);
        labels.erase(labels.begin() + random_variable);
    }
    Eigenfaces eigenfaces(training,trainingLabels,atoi(argv[2]),atoi(argv[3]));
    int error =0;
    for(int i=0;i<images.size();i++){
        int predicted = eigenfaces.predict(images.at(i));
        //cout << "actual=" << labels.at(i) << " / predicted=" << predicted << endl;
        if(predicted!=labels.at(i))
            error++;
    }

    cout << error*100.0/images.size() << endl;

    if(argc==5){
        csv = string(argv[4]);
        images.clear();
        labels.clear();
        try {
            read_csv(csv, images, labels);
        } catch(exception& e) {
            cerr << "Error opening file \"" << csv << "\"." << endl;
            exit(1);
        }

        error =0;
        for(int i=0;i<images.size();i++){
            int predicted = eigenfaces.predict(images.at(i));
            if(predicted!=labels.at(i))
                error++;
        }
        cout << error*100.0/images.size() << endl;
    }

    return 0;
}