#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <sstream>

#include "opencv2/opencv.hpp"
#include "frameProcessor.h"

using namespace cv;
using namespace std;

class videoProcessor{
private:
    VideoCapture caputure;
    VideoWriter writer;
    string outputFileName;

    int currentIndex;
    int digits;
    string extension;
    FrameProcessor *frameprocessor;

    /**
     * the function to process each frame in the video
     */
    void (*process)(Mat &,Mat &);
    /**
     * @brief callIt whwther to call the process function or class
     */
    bool callIt;

    string windowNameInput;
    string windowNameOutput;

    /**
     * @brief delay the inteval time to delay
     */
    int delay;

    /**
     * @brief frameToStop which frame in the video to stop
     */
    long frameToStop;

    /**
     * @brief stop whether the video is stopped
     */
    bool stop;

    /**
     * @brief images the image names to be used as input video stream
     */
    vector<string> images;
    vector<string>::const_iterator itImg;
public:
    videoProcessor();

    /**
     * @brief setFrameProcessor set the function to process each frame in the video
     */
    void setFrameProcessor(void (*process)(Mat &,Mat &));

    /**
     * @brief setFrameProcessor set the frame process class to process each frame in the video
     * @param frameprocessor intance of Frame processor
     */
    void  setFrameProcessor(FrameProcessor *frameprocessor);

    /**
     * @brief setInput open the video according to filename
     * @param filename the video name yo open
     * @return  whether the video is opened correctly
     */
    bool setInput(const string &filename);

    /**
     * @brief setInput set the image sequence as input
     * @param imgs image sequence
     * @return
     */
    bool setInput (const vector<string> &imgs);

    /**
     * @brief createWinToDispInput set the window to display input video
     * @param winName the window name you want to set for video
     */
    void createWinToDispInput(const string& winName);

    /**
     * @brief displayOutput set the window to display output video
     * @param winName
     */
    void createWinToDispOutput(const string& winName);

    /**
     * @brief releaseDisplayWindow release the display window
     */
    void releaseDisplayWindow();

    /**
     * @brief run start to play the video
     */
    void run();

    /**
     * @brief isStopped return the state of stop
     * @return
     */
    inline bool isStopped() const {return stop;}

    /**
     * @brief isOpened whether the input video or image squence is opened correctly
     * @return
     */
    inline bool isOpened() const {return  caputure.isOpened ()||!images.empty ();}

    /**
     * @brief setDelay set the delay time
     * @param d the delay time
     */
    inline void setDelay(int d){delay = d;}

    /**
     * @brief callProcess set the flag to call the process function or class
     */
    inline void callProcess(){callIt = true;}

    /**
     * @brief dontCallProcess unset the flag to not call the process function or class
     */
    inline void  dontCallProcess(){callIt = false;}

    /**
     * @brief setFrameNumToStop set the frame number to stop
     * @param frame
     */
    inline void setFrameNumToStop(long frame){frameToStop = frame;}

    /**
     * @brief getFrameNumber get current frame position of video
     * @return
     */
    inline long getCurrentFrameNumber(){return static_cast<long>(caputure.get((CV_CAP_PROP_POS_FRAMES)));}

    /**
       * @brief getFrameSize return the size of each frame
       * @return
       */
    Size getFrameSize();

    /**
      * @brief getFrameRate get the frame rate of the video
      * @return
      */
     inline double getFrameRate(){return caputure.get(CV_CAP_PROP_FPS);}

     /**
      * @brief getCodec get the decode type of the video
      * @param codec
      * @return
      */
     int getCodec(char (&codec)[4]);

     /**
      * @brief setOutput save the process result as a video
      * @param filename output video name
      * @param codec code type
      * @param framerate frame rate
      * @param isColor
      * @return
      */
     bool setOutput(const string &filename,int codec = 0,double framerate = 0.0,bool isColor = true);

     /**
      * @brief setOutput save the process result as image sequence
      * @param filename path to save image
      * @param ext the format of the saved image
      * @param numberOfDigits
      * @param startIndex
      * @return
      */
     bool setOutput (const string &filename, const string &ext, int numberOfDigits=3, int startIndex=0 );

private :
    /**
     * @brief stopIt stop the video
     */
    inline void stopIt(){stop = true;}

    /**
     * @brief readNextFrame read the next frame in the video or image sequence
     * @param frame returned image
     * @return if success, return true; otherwise, return false
     */
    bool readNextFrame(Mat &frame);

    /**
     * @brief writeNextFrame write the next frame
     * @param frame the frame to write
     */
    void writeNextFrame(Mat &frame);
};

#endif // videoProcessor_H
