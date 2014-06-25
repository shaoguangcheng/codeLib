#include "cv_lib.h"
#include "cv.hpp"

/**
 * @brief DOG difference of gaussian
 * @param src
 * @param dst
 * @return
 */
int DOG(const cv::Mat src,cv::Mat &dst)
{
    if(src.empty())return 1;

    cv::Mat img_1,img_2;

    cv::GaussianBlur(src,img_1,cv::Size(3,3),0,0);
 //   cv::GaussianBlur(src,img_2,cv::Size(3,3),0,0);
    cv::GaussianBlur(img_1,img_2,cv::Size(3,3),0,0);

    dst = img_1 - img_2;
    cv::normalize(dst,dst,255,0,CV_MINMAX);

    return 0;
}
/**
 * @brief Laplace Laplace transform
 * @param src
 * @param dst
 * @return
 */

int Laplace(const cv::Mat src,cv::Mat &dst)
{
    if(src.empty())return 1;

    cv::Laplacian(src,dst,8,3);

    cv::normalize(dst,dst,255,0,CV_MINMAX);

    return 0;
}

int detectSkin(cv::Mat &src,cv::Mat &dst)
{
    cv::Mat skinCrCbHist = cv::Mat::zeros(src.size(),CV_8UC1);
    cv::ellipse(skinCrCbHist,cv::Point2f(src.rows/2.0,src.cols/2.0),cv::Size(23.4,15.2),43.0,0,360,cv::Scalar(255,255,255),-1);

    cv::Mat YrCrCbImage;
    cv::Mat outPutMask = cv::Mat::zeros(src.size(),CV_8UC1);

    cv::Mat element = cv::getStructuringElement(1,cv::Size(3,3),cv::Point(-1,-1));

    cv::cvtColor(src,YrCrCbImage,CV_BGR2YCrCb);
    cv::imshow("yrcrcb",YrCrCbImage);
    cv::imshow("ellipse",skinCrCbHist);
    cv::imwrite("YrCrCb.png",YrCrCbImage);

    for(int i=0;i<src.rows;i++){
        unsigned char *p = outPutMask.ptr<unsigned char>(i);
        cv::Vec3b *ycrcb = YrCrCbImage.ptr<cv::Vec3b >(i);
        for(int j=0;j<src.rows;j++){
            if(skinCrCbHist.at<unsigned char>(ycrcb[j][1],ycrcb[j][2])>0)
                p[j] = 255;
        }
    }
    cv::imshow("outPutMask",outPutMask);
//    cv::morphologyEx(outPutMask,outPutMask,1,element);

    std::vector<std::vector<cv::Point> > contours;
    std::vector<std::vector<cv::Point> > filterContours;

    cv::findContours(outPutMask,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);

    std::vector<std::vector<cv::Point> > ::iterator it;
    for(it = contours.begin();it != contours.end();it++){
        if(fabs(cv::contourArea(*it)) > 100){
            filterContours.push_back(*it);
        }
    }

    outPutMask.setTo(0);
    cv::drawContours(outPutMask,filterContours,-1,cv::Scalar(255,0,0),CV_FILLED);


    src.copyTo(dst, outPutMask);

    cv::imshow("skin",dst);

    outPutMask.setTo(0);

    cv::waitKey();

    return 0;
}
