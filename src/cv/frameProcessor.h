#ifndef FRAMEPROCESSOR_H
#define FRAMEPROCESSOR_H

#include <opencv2/core/core.hpp>

using namespace cv;

class FrameProcessor{
    public:
        virtual void process(Mat &input,Mat &output)=0;
};

#endif // FRAMEPROCESSOR_H
