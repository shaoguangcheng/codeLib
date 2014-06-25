#include "videoProcessor.h"
#include "frameProcessor.h"

#include <string>

using namespace cv;

void process(Mat& in, Mat& out)
{
    int channels = in.channels();
    if(channels == 3)
        cvtColor(in, out, CV_BGR2GRAY);
}

class frameProcessor : public FrameProcessor
{
public :
    void process(Mat &input,Mat &output){
        ::process(input, output);
    }
};

int main(int argc, char* argv[])
{
    if(argc != 2){
        cout << "usage : program video|imageSequence" << endl;
        return -1;
    }

    string fileName(argv[1]);
    frameProcessor frame;
    videoProcessor processor;

    processor.setInput(fileName);
    processor.createWinToDispInput("input");
    processor.createWinToDispOutput("output");
    processor.setDelay(1000./processor.getFrameRate());
    processor.setFrameProcessor(&frame);

    processor.run();

    processor.releaseDisplayWindow();

    return 0;
}
