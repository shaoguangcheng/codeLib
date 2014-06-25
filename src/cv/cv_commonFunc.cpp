#include "cv_commonFunc.h"



int csg::convertVideoToImageSequence(string videoPath, string pathToSaveImages)
{
    VideoCapture video;

    cout << videoPath;
    video.open(videoPath);
    if(!video.isOpened()){
        cout << "can not open the video!" << endl;
        return -1;
    }
	
    Mat frame;
    char num[20];
    int key = 0;

    int i = 0;
    while( key != 27 ){
        video >> frame;
        if(frame.empty())break;

        sprintf(num,"%d",i);
        string seq(num);
        imwrite(pathToSaveImages+seq+".png",frame);

        i++;
    }
    return 0;
}

int csg::videoGenerator(vector<Mat> &images,string videoName)
{
    if(images.size() == 0){
        cout << "there id no images to generate video" << endl;
        return -1;
    }

    cout << images.size() << endl;
    vector<Mat>::iterator it;
    VideoWriter video;
    Mat img = images[0];

    const int fps = 10;

    video.open(videoName,CV_FOURCC('D','I','V','X'),fps,Size(img.cols,img.rows));
    if(!video.isOpened()){
        cout << "can not open video write "<<endl;
        return -1;
    }

    for(it = images.begin();it != images.end();it++){
        img = *it;

        video.write(img);
    }

    video.release();
    return 0;
}
