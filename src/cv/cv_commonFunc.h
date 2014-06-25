#ifndef CV_COMMONFUNC_H
#define CV_COMMONFUNC_H

#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;

namespace csg{
/**
     * @brief convertVideoToImageSequence   convert video to images
     * @param videoPath   the video you want convert
     * @param pathToSaveImages  path  you specified to save images
     * @return uccess 0; fail -1.
     */
    int convertVideoToImageSequence(string videoPath, string pathToSaveImages="./");

    /**
     * @brief videoGenerator  using images to generate video.(for professional use, you need to modify the function source code.
     * this function is written badly.)
     * @param images  image set to generate video
     * @param videoName
     * @return success 0; fail -1.
     */
    int videoGenerator(vector<Mat> &images,string videoName);
} // end of namespace csg

#endif // CV_COMMONFUNC_H










