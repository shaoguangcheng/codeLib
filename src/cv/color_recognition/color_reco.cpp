#include <cv.h>
#include <highgui.h>
#include"string"
#include"CRecognition.h"
#include"color_reco.h"
#include"time.h"
using namespace cv;


int main(int argc,char* argv[])
{
    if(!test_video(argc,argv))
        printf("test video successfully!\n");
//    test_image(argc,argv);
}

//save file

int write_file(const char* file_name,int* data,int n)
{
    FILE *fp;

    fp = fopen(file_name,"w");
    if(fp == NULL){
        printf("can not open the file\n");
        return -1;
    }
    int num = 0;
    for(int i =0;i<n;i++){
        fprintf(fp,"%d ",data[i]);
        num++;
//        if(num == 20){
//            num = 0;
//            fprintf(fp,"\n");
//        }
    }
    fclose(fp);
}

int write_file(const char* file_name,double* data,int n)
{
    FILE *fp;

    fp = fopen(file_name,"w");
    if(fp == NULL){
        printf("can not open the file\n");
        return -1;
    }
    int num = 0;
    for(int i =0;i<n;i++){
        fprintf(fp,"%lf ",data[i]);
        num++;
//        if(num == 20){
//            num = 0;
//            fprintf(fp,"\n");
//        }
    }
    fclose(fp);
}

//trace color region by given pixel
SPixelPosition color_reco(CRawImage* image,unsigned char* learn_pixel)
{
    CRecognition *recognition;
    recognition = new CRecognition();
    SPixelPosition pos;

    recognition->learnPixel(learn_pixel);
    pos = recognition->findSegment(image);

    return pos;//return the center of the objected region
}
//extract a single channel of an image
int extract_channel(Mat image_src,Mat &image_dst,int channel)
{
   int w,h;

   w = image_src.cols;
   h = image_src.rows;

   if(image_src.channels()!=3){
       printf("can not extract the channel\n");
       return -1;
   }
   for(int i =0;i<w*h;i++){
       image_dst.data[i] = image_src.data[i*3+channel];
   }
   return 0;
}

//draw the contour of objects in a picture
RotatedRect ellipse_detect(Mat src_img)
{
//    if(src_img.empty()) return -1;

    Mat gray_img, bin_img;
    RotatedRect box ;
    cvtColor(src_img, gray_img, CV_BGR2GRAY);

    std::vector<std::vector<cv::Point> > contours;

    threshold(gray_img, bin_img, 0, 255, cv::THRESH_BINARY|cv::THRESH_OTSU);

    findContours(bin_img, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    for(int i = 0; i < contours.size(); ++i) {
      size_t count = contours[i].size();
      if(count < 150 || count > 1000) continue;

      Mat pointsf;
      Mat(contours[i]).convertTo(pointsf, CV_32F);
      box = fitEllipse(pointsf);
    }
    return box;
}

int test_video(int argc,char* argv[])
{
    VideoCapture video;
    Mat image_in,*image_out;
    user_data param;

//    RotatedRect box;

    unsigned char learn_pixel[3]={222,9,8};
    SPixelPosition pos;pos.

    int w = 0,h = 0;
    int time_delay = 20;
    char key = 0;
    int nframe = 0;

    if(argc < 2){
        printf("please input the video name\n");
        exit(1);
    }
    video.open(argv[1]);
    if(!video.isOpened()){
        printf("Failed to open video file: %s\n",argv[1]);
        exit(1);
    }

    //get first frame
    video >> image_in;
    nframe = video.get(CV_CAP_PROP_FRAME_COUNT);

    int *dot;
    dot  = new int [nframe-2];

    double *time;
    time = new double [nframe-2];

    w = image_in.cols;
    h = image_in.rows;

//    box = ellipse_detect(image_in);
//    ellipse(image_in, box, Scalar(0,0,0), 2, CV_AA);

    CRawImage image(w,h);
    image.from_mat(&image_in);

    pos = color_reco(&image,learn_pixel);
    printf("pos.x = %d,pos.y = %d\n,maxSize = %d\n",pos.x,pos.y,pos.max_size);

//    dot[0] = pos.max_size;

    image_out = image.to_mat();

    imshow("color_detection",*image_out);
    key = waitKey(time_delay);

    int64 t1 = 0;
    int64 t2 = 0;
    double dt = 1/getTickFrequency();

    param.w = image_in.cols;
    param.data = image_in.data;
    param.pixel = learn_pixel;

    t1 = getTickCount();

    int i=0;
    char num[20];
    while(key != 27 ){
        setMouseCallback("color_detection",on_mouse,&param);
        //get next frame
        video >> image_in;
        if(image_in.empty())break;

        CRawImage image(w,h);
        image.from_mat(&image_in);

        pos = color_reco(&image,learn_pixel);
        t2 =getTickCount();

        time[i] = (t2-t1)*dt;
        dot[i] = pos.max_size;

        printf("x = %d,y = %d\n",pos.x,pos.y);
        printf("time     = %f \n",(t2-t1)*dt);
        printf("maxSize  = %d \n",dot[i]);
        i++;

        image_out = image.to_mat();

        sprintf(num,"%d",i);
        string seq(num);

        char center[20],maxSize[20],dist_str[20];
        double dist = 0;

        dist = 0.3*sqrt(2550.0/pos.max_size);

        sprintf(center,"center   = (%d,%d)",pos.x,pos.y);
        sprintf(maxSize,"maxSize = %d",pos.max_size);
        sprintf(dist_str,"depth   = %f",dist);

        putText(*image_out,center,Point(0,40),2,0.5,Scalar(25,200,25));
        putText(*image_out,maxSize,Point(0,20),2,0.5,CV_RGB(25,200,25));
        putText(*image_out,dist_str,Point(0,60),2,0.5,CV_RGB(25,200,25));

        imshow("color_detection",*image_out);

        imwrite("image_temp/"+seq+".jpg",*image_out);
        key = waitKey(50);
    }

    //calculate distance
    double init_distance = 0.6;
    double *distance;
    distance = new double [nframe - 2];

    distance[0] = init_distance;
    for(int j = 1;j < nframe-2;j++){
        if(dot[j]>=2*dot[j-1])
            dot[j] = dot[j-1];
        distance[j] = distance[j-1]*sqrt((double)dot[j-1]/dot[j]);
    }

    write_file("distance",distance,nframe-2);
    write_file("num_dot",dot,nframe-2);
    write_file("time",time,nframe-2);

    return 0;
}
//the callback of LMOUSEDOWN event
void on_mouse(int event,int x,int y,int flags,void* param)
{
    user_data* dat = (user_data*)param;
    int w = dat->w;
    if(event == EVENT_LBUTTONDOWN){
        for(int i =0;i<3;i++){
            dat->pixel[i] = dat->data[(y*w+x)*3+2-i];
        }
    }
}

int test_image(int argc,char* argv[])
{
    Mat img_in,red_channel;
    img_in = imread("test.jpg");

    int w = img_in.cols;
    int h = img_in.rows;
    printf("w = %d,h = %d\n",w,h);

    //extract red channel
    red_channel.create(h,w,CV_8UC1);
    extract_channel(img_in,red_channel,2);

    imshow("original",red_channel);
    imshow("original picture",img_in);
    waitKey();

    CRawImage image(w,h);
    image.from_mat(&img_in);

    unsigned char learn_pixel[3]={255,0,0};
    SPixelPosition pos = color_reco(&image,learn_pixel);
    printf("pos.x = %d,pos.y = %d\n",pos.x,pos.y);

    Mat* img_out;
    img_out = image.to_mat();

    imshow("color_detection",*img_out);
    waitKey();

    return 0;
}
