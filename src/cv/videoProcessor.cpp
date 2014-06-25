#include "videoProcessor.h"

#include <iomanip>

using namespace std;

 videoProcessor::videoProcessor() : callIt(true),delay(0),stop(false),digits(0),frameToStop(-1)
 {}

 void videoProcessor::setFrameProcessor(void (*process)(Mat &,Mat &)){
     frameprocessor = 0;
     this->process = process;
     callProcess ();
 }

 void videoProcessor::setFrameProcessor(FrameProcessor *frameprocessor){
     process = 0;
     this->frameprocessor = frameprocessor;
     callProcess ();
 }

 bool videoProcessor::setInput(const string& filename){
     /**
      * if the capture has opened some video, release it
      */
     caputure.release ();
     return caputure.open (filename);
 }

 bool videoProcessor::setInput (const vector<string> &imgs){
     caputure.release ();
     images = imgs;
     itImg = images.begin ();
     return true;
 }

 void videoProcessor::createWinToDispInput(const string& winName){
     windowNameInput = winName;
     namedWindow (windowNameInput);
 }

 void videoProcessor::createWinToDispOutput(const string& winName){
     windowNameOutput = winName;
     namedWindow (windowNameOutput);
 }

 void videoProcessor::releaseDisplayWindow(){
     destroyWindow (windowNameInput);
     destroyWindow (windowNameOutput);
     windowNameInput.clear ();
     windowNameOutput.clear ();
 }

 void videoProcessor::run(){
     Mat frame;
     Mat output;
     if(!isOpened())
         return;
     stop = false;
     while(!isStopped()){
         /**
          * read the next frame
          */
         if(!readNextFrame(frame))
             break;

         /**
          * display the input video
          */
         if(windowNameInput.length ()!=0)
             imshow (windowNameInput,frame);

         /**
          * process current frame
          */
         if(callIt){
             if(process)
                 process(frame,output);
             else if(frameprocessor)
                 frameprocessor->process (frame,output);
         }
         else{
             output = frame;
         }

         /**
          * save the frame
          */
         if(outputFileName.length()){
                 cvtColor(output,output,CV_GRAY2BGR);
                 writeNextFrame(output);
           }

         /**
          * display output video
          */
         if(windowNameOutput.length()!=0)
             imshow (windowNameOutput,output);

         /**
          * if we set the delay time, then when dely time is reached or we tap a key, the video is gonging on
          */
         if(delay>=0&&waitKey(delay)>=0)
             waitKey(0);

         /**
          * if we set frameToStop, then when reaching the specified position, the video stop
          */
         if(frameToStop>=0&&getCurrentFrameNumber()==frameToStop)
             stopIt();
     }
 }

 bool videoProcessor::readNextFrame(Mat &frame){
     if(images.size ()==0)
         return caputure.read(frame);
     else{
         if(itImg!=images.end()){
             frame = imread(*itImg);
             itImg++;
             return frame.data?1:0;
         }
         else
             return false;
     }
 }

 void videoProcessor::writeNextFrame(Mat &frame){
     /**
      * if the extentionis not null, then we save the frame as an image; if null, then we write the frame into output video
      */
     if(extension.length()){
         stringstream ss;
         ss<<outputFileName<<setfill('0')<<setw(digits)<<currentIndex++<<extension;
         imwrite(ss.str(),frame);
     }
     else{
         writer.write (frame);
     }
 }

 Size videoProcessor::getFrameSize() {
    if (images.size()==0) {
        int w= static_cast<int>(caputure.get(CV_CAP_PROP_FRAME_WIDTH));
        int h= static_cast<int>(caputure.get(CV_CAP_PROP_FRAME_HEIGHT));
        return Size(w,h);
        }
    else {
            cv::Mat tmp= cv::imread(images[0]);
            return (tmp.data)?(tmp.size()):(Size(0,0));
        }
      }

 int videoProcessor::getCodec(char (&codec)[4]) {
     if (images.size()!=0)
         return -1;

     /**
       * define the structure to return the codec
       */
     union {
         int value;
         char code[4];
     } type;

     type.value= static_cast<int>(caputure.get(CV_CAP_PROP_FOURCC));

     codec[0]= type.code[0];
     codec[1]= type.code[1];
     codec[2]= type.code[2];
     codec[3]= type.code[3];
     return type.value;
 }

 bool videoProcessor::setOutput(const string &filename,int codec, double framerate ,bool isColor){
     outputFileName = filename;
     extension.clear ();
     if(framerate ==0.0){
         framerate = getFrameRate();
     }

     char c[4];
     if(codec==0){
         codec = getCodec(c);
     }
     return writer.open(outputFileName,
                        codec,
                        framerate,
                        getFrameSize(),
                        isColor);
 }

 bool videoProcessor::setOutput (const string &filename, const string &ext, int numberOfDigits, int startIndex){
        if(numberOfDigits<0)
            return false;
        outputFileName = filename;
        extension = ext;
        digits = numberOfDigits;
        currentIndex = startIndex;
        return true;
 }
