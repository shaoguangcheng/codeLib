#include "../src/cv/cv_lib.h"
#include "../src/cv/cv_grid.h"
#include "../src/cv/cv_commonFunc.h"
#include "../src/cv/videoProcessor.h"
#include "../src/cv/frameProcessor.h"

#include <stdlib.h>
#include <stdio.h>
#include <exception>

#include "iostream"
#define main_func 8

using namespace csg;
void main_DOG(int argc,char* argv[])
{
    if(argc<2){
        std::cout << "parameter is not enough\n";
        return;
    }

    cv::Mat image,image_out;
    image = cv::imread(argv[1]);
    DOG(image,image_out);

    cv::imshow("DOG",image_out);
    cv::imwrite("../image/DOG.png",image_out);
    cv::waitKey();
}

void main_Laplacian(int argc,char* argv[])
{
    if(argc<2){
        std::cout << "parameter is not enough\n";
        return;
    }
	string ss;
    cv::Mat image,image_out;
    image = cv::imread(argv[1]);

    Laplace(image,image_out);

    cv::imshow("lap",image_out);
    cv::imwrite("../image/Laplacian.png",image_out);
    cv::waitKey();
}

void main_pryUpDown(int argc,char* argv[])
{
    if(argc<2){
        std::cout << "parameter is not enough\n";
        return;
    }

    cv::Mat image,image_out;
    image = cv::imread(argv[1]);

    cv::pyrDown(image,image_out);
    cv::pyrUp(image_out,image_out);

    image_out = image - image_out;

    cv::imshow("lap",image_out);
    cv::imwrite("../image/up_down.png",image_out);
    cv::waitKey();
}
void test_mat()
{
    cv::Mat M = (cv::Mat_<cv::Vec2d>(2,2)<<cv::Vec2d(1,1),cv::Vec2d(2,2),cv::Vec2d(4,4),cv::Vec2d(5,5));
    std::cout << M <<std::endl;

    cv::Mat M1;
    M1.create(2,2,CV_32FC1);
    M1 = M.clone();

    std::cout << M1 <<std::endl;

    cv::Mat M2 = cv::Mat_<int>(3,3);

    M2.at<int>(2,1) = 100;
    M2.ptr<int>(0)[0] = 10;
    std::cout << M2.at<int>(2,2)<<std::endl;
    std::cout << M2.ptr<int>(2)[1]<<std::endl;

    cv::Mat M3 = cv::Mat_<double>(5,1);

    M3.at<double>(3,0) = 10;
    std::cout << M3.ptr<double>(3)[0]<<std::endl;

}

void main_detectSkin(int argc,char* argv[])
{
    if(argc<2){
        std::cout << "parameter is not enough\n";
        return;
    }

    cv::Mat image,imageOut;
    image = cv::imread(argv[1]);

    detectSkin(image,imageOut);

  //  cv::imshow("lap",image_out);
  //  cv::imwrite("../image/up_down.png",image_out);
  // cv::waitKey();
}


void main_test_convertVideoToImageSequence(int argc,char* argv[])
{
    if(argc < 2){
        cout << "[usage]: ./test_cv.e videoPath [pathToSaveImage]"<<endl;
        return;
    }
    string videoName(argv[1]);

    convertVideoToImageSequence(videoName,"../video/");

}

void main_testVideoGenerate(int argc,char* argv[])
{
    if(argc < 3){
        cout << "[usage]: ./test_cv.e videoPath videoName"<<endl;
        return;
    }

    int i = 0;
    vector<Mat> images;
    Mat frame;
    char num[20];

    while(1){

        sprintf(num,"%d",i);
        string seq(num);

        frame = imread("../image_temp/"+seq+".png");
        if(!frame.empty()){

            Mat temp;
            temp.create(Size(frame.cols,frame.rows),CV_8UC3);

            imwrite("temp.jpg",frame);
            temp = imread("temp.jpg");

            images.push_back(temp);
            imshow("demo",temp);
        }
        waitKey(50);
        i++;
        if(i>400)break;
    }

    videoGenerator(images,argv[2]);

}

void main_grid(int argc,char* argv[])
{
    Mat image(500,500,CV_8UC3);

    memset(image.data,0,image.total());

    grid gridImage;
    gridImage.init(image,10,10);
    gridImage.drawGrid();

    try{
        gridImage.setRectColor(Scalar(255,0,0));
        gridImage.fillRect(Point(1,2));
        gridImage.fillRect(Point(2,3));
        gridImage.setRectColor(Scalar(0,0,255));
        gridImage.fillRect(Point(3,4));
        gridImage.fillRect(Point(3,5));
        gridImage.fillRect(Point(3,6));
        gridImage.fillRect(Point(3,7));
        gridImage.fillRect(Point(3,8));
        gridImage.setRectColor(Scalar(255,0,0));
        gridImage.fillRect(Point(3,9));
        gridImage.fillRect(Point(3,10));
        gridImage.showGrid();
    } catch (range_error error){
        cout << error.what() << endl;
    }

//    floodFill2(gridImage,Point(10,9),Scalar(0,0,0),Scalar(255,125,125));
    floodFill3(gridImage,Point(10,9),Scalar(0,0,0),Scalar(255,125,125));
    waitKey();
}

int main(int argc,char* argv[])
{
    if(0 == main_func)main_DOG(argc,argv);
    if(1 == main_func)main_Laplacian(argc,argv);
    if(2 == main_func)main_pryUpDown(argc,argv);
    if(3 == main_func)test_mat();
    if(4 == main_func)main_detectSkin(argc,argv);
    if(5 == main_func)main_test_convertVideoToImageSequence(argc,argv);
    if(6 == main_func)main_testVideoGenerate(argc,argv);
    if(7 == main_func)main_grid(argc,argv);

    return 0;
}
