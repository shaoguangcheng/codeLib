#ifndef CV_LIB_H
#define CV_LIB_H

#include <opencv/cv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>

int DOG(const cv::Mat src,cv::Mat &dst);
int Laplace(const cv::Mat src,cv::Mat &dst);

int detectSkin(cv::Mat &src,cv::Mat &dst);

void equalizeHist(cv::Mat &src,cv::Mat &dst);

#endif









