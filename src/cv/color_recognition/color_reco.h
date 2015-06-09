#ifndef COLOR_RECO_H
#define COLOR_RECO_H

#include<cv.h>
#include<highgui.h>
using namespace cv;
//assert functions and data format defined by myself
int test_video(int argc,char* argv[]);
RotatedRect ellipse_detect(Mat src_img);
int test_image(int argc,char* argv[]);

struct user_data{
    int w;                  //the width of image
    unsigned char* data;    //the data region pointer of image
    unsigned char* pixel;   //the pixel you want to trace
};

void on_mouse(int event,int x,int y,int flags,void* param);//the callback of LMOUSEDOWN event

#endif // COLOR_RECO_H
