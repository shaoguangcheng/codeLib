#include <cv.h>
#include<highgui.h>
#include"cluster.h"

using namespace cv;
using namespace std;

double color_diff(double d1, double d2, double d3)
{
    double m, sd;

    m = (d1+d2+d3)/3.0;
    //sd = sqr(d1-m) + sqr(d2-m) + sqr(d3-m);
    //sd = fabs(d1-m) + fabs(d2-m) + fabs(d3-m);
    sd = d1+d2+d3;
    return sd;
}

int image_diff(Mat &img_in, Mat &img_diff, double sigma=300)
{
    int     w, h;
    int     i, j;
    int     im, ip, jm, jp;

    unsigned char   *pix;
    double          *pix_o;

    double  f1, f2, f3;
    double  d, d1, d2, d3;

    // get w/h
    w = img_in.cols;
    h = img_in.rows;

    // create output image
    img_diff.create(h, w, CV_64FC1);

    pix   = img_in.data;
    pix_o = (double *) img_diff.data;

    for(j=0; j<h; j++) {
        jm = j-1;
        jp = j+1;
        if( j == 0 )  jm = h-1;
        if( j == h-1) jp = 0;

        for(i=0; i<w; i++) {
            im = i-1;
            ip = i+1;
            if( i == 0 )  im = w-1;
            if( i == w-1) ip = 0;

            d = 0;

            f1 = pix[j*w*3+i*3+0];
            f2 = pix[j*w*3+i*3+1];
            f3 = pix[j*w*3+i*3+2];

            // j-1
            d1 = fabs(f1 - pix[jm*w*3+im*3+0]);
            d2 = fabs(f2 - pix[jm*w*3+im*3+1]);
            d3 = fabs(f3 - pix[jm*w*3+im*3+2]);
            d += color_diff(d1, d2, d3);

            d1 = fabs(f1 - pix[jm*w*3+i*3+0]);
            d2 = fabs(f2 - pix[jm*w*3+i*3+1]);
            d3 = fabs(f3 - pix[jm*w*3+i*3+2]);
            d += color_diff(d1, d2, d3);

            d1 = fabs(f1 - pix[jm*w*3+ip*3+0]);
            d2 = fabs(f2 - pix[jm*w*3+ip*3+1]);
            d3 = fabs(f3 - pix[jm*w*3+ip*3+2]);
            d += color_diff(d1, d2, d3);

            // j
            d1 = fabs(f1 - pix[j*w*3+im*3+0]);
            d2 = fabs(f2 - pix[j*w*3+im*3+1]);
            d3 = fabs(f3 - pix[j*w*3+im*3+2]);
            d += color_diff(d1, d2, d3);

            d1 = fabs(f1 - pix[j*w*3+ip*3+0]);
            d2 = fabs(f2 - pix[j*w*3+ip*3+1]);
            d3 = fabs(f3 - pix[j*w*3+ip*3+2]);
            d += color_diff(d1, d2, d3);

            // j+1
            d1 = fabs(f1 - pix[jp*w*3+im*3+0]);
            d2 = fabs(f2 - pix[jp*w*3+im*3+1]);
            d3 = fabs(f3 - pix[jp*w*3+im*3+2]);
            d += color_diff(d1, d2, d3);

            d1 = fabs(f1 - pix[jp*w*3+i*3+0]);
            d2 = fabs(f2 - pix[jp*w*3+i*3+1]);
            d3 = fabs(f3 - pix[jp*w*3+i*3+2]);
            d += color_diff(d1, d2, d3);

            d1 = fabs(f1 - pix[jp*w*3+ip*3+0]);
            d2 = fabs(f2 - pix[jp*w*3+ip*3+1]);
            d3 = fabs(f3 - pix[jp*w*3+ip*3+2]);
            d += color_diff(d1, d2, d3);

            pix_o[j*w+i] = exp(-d/sigma);
            //pix_o[j*w+i] = d;
        }
    }


    return 0;
}
#if 0
int image_diff(Mat &image_in,Mat &image_diff,double sigma)
{
    int w,h;
    int i_next,j_next,i_previous,j_previous;
    double d = 0;

    w = image_in.cols;
    h = image_in.rows;

    double *pixel;
    image_diff.create(h,w,CV_32FC1);
    pixel = (double*)image_diff.data;

    for(int i=0;i<h;i++){
        if(i == 0)
            i_previous = h;
        else
            i_previous = i-1;

        if(i == h)
            i_next = 0;
        else
            i_next = i+1;

        for(int j=0;j<w;j++){
            if(j == 0)
                j_previous = w;
            else
                j_previous = j-1;
            if(j == w)
                j_next = 0;
            else
                j_next = j+1;

            d = 0;

            d += fabs(image_in.data[w*i+j] - image_in.data[w*i_previous+j_previous]);
            d += fabs(image_in.data[w*i+j] - image_in.data[w*i_previous+j]);
            d += fabs(image_in.data[w*i+j] - image_in.data[w*i_previous+j_next]);
            d += fabs(image_in.data[w*i+j] - image_in.data[w*i+j_previous]);
            d += fabs(image_in.data[w*i+j] - image_in.data[w*i+j_next]);
            d += fabs(image_in.data[w*i+j] - image_in.data[w*i_next+j_previous]);
            d += fabs(image_in.data[w*i+j] - image_in.data[w*i_next+j]);
            d += fabs(image_in.data[w*i+j] - image_in.data[w*i_next+j_next]);

            d = exp(-d/sigma);

            pixel[w*i+j] = d;
        }
    }

   return 0;
}
#endif

int image_to_8uc1(Mat &img, Mat &img_o)
{
    int     w, h;
    double  *p;

    unsigned char   *pu8;

    int     i;
    double  v_max, v_min, v;
    double  d;
    int     iv;

    w = img.cols;
    h = img.rows;

    p = (double*) img.data;

    img_o.create(h, w, CV_8UC1);
    pu8 = img_o.data;

    // find max/min
    v_max = -1e30;
    v_min =  1e30;
    for(i=0; i<w*h; i++) {
        v = p[i];
        if( v > v_max ) v_max = v;
        if( v < v_min ) v_min = v;
    }

    d = 255.0/(v_max - v_min);

    for(i=0; i<w*h; i++) {
        iv = (p[i] - v_min)*d;
        pu8[i] = iv;
    }
}


Point vanish_point(Mat &image)
{
    Mat img_resize,img_gray,img_equ_hist,img_canny;
    Point pos;

    Size dsize;
    vector<Vec4i> lines;
    int tolerance = 20;

    img_gray.create(image.rows,image.cols,CV_8UC1);

    dsize.height = 400;
    dsize.width  = 400;

    //resize image
    resize(image,img_resize,dsize);
//    imshow("resize",img_resize);

    //convert image to gray
    if(img_resize.channels()==3){
        cvtColor(img_resize,img_gray,CV_BGR2GRAY);
   }
    else
        img_gray = img_resize;
//    imshow("gray",img_gray);

    //histogram equalize
    equalizeHist(img_gray,img_equ_hist);
//    imshow("equa_hist",img_equ_hist);

    //apply canny
    Canny(img_equ_hist,img_canny,50,200);
//    imshow("canny",img_canny);

   // apply 45 degree filter
//    filter2D(img_canny,img_filter,CV_8U,img_kernel);
//    imshow("filter",img_filter);

    //apply hough transform
    HoughLinesP(img_canny,lines,1,CV_PI/180,50,20,10);

    //draw the hough result
    vector<Vec4i>::iterator it_0 = lines.begin();
    int line_num = 0;
    vector<double> data;
    for(;it_0!=lines.end();it_0++){
        Vec4i l = *it_0;
        if(fabs(l[0]-l[2])<tolerance||fabs(l[1]-l[3])<tolerance)
            continue;

        for(int i=0;i<4;i++){
            data.push_back(l[i]);
        }

        //draw the start and end point
        circle(img_resize,Point(l[0],l[1]),2,Scalar(0,0,255));
        circle(img_resize,Point(l[2],l[3]),2,Scalar(0,0,255));

        //draw the line
        line(img_resize,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(255,0,0),1,CV_AA);
        line_num++;
    }


#if 0
    Mat sample,center,label;

    sample.create(line_num*2,1,CV_32FC2);
    center.create(4,1,CV_32FC2);
    label.create(line_num*2,1,CV_32FC1);

    vector<int>::iterator it_2;
    int i = 0;
    for(it_2 = data.begin();it_2!=data.end();it_2++){
        sample.data[2*i] = *it_2;
        it_2++;
        sample.data[2*i+1] = *it_2;
        i++;
    }
#endif

#if 0
    vector<Vec2i> sample;
    vector<int> label;
    vector<Vec2i> center;
    vector<int>::iterator it_2;
    int dot = 0;
    for(it_2 = data.begin();it_2!=data.end();it_2+=2){
        Vec2i s;
        s[0] = *it_2;N
        s[1] = *(it_2+1);

        sample.push_back(s);

        dot++;
    }
#endif

    //define relative variables in order to cluster
    int i = 0,j = 0;
    long N = line_num*2;
    int K =4,D = 2;

    double** sample = (double**)calloc(N,sizeof(double*));
    for(i =0;i<N;i++){
        sample[i] = (double*)calloc(D,sizeof(double));
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<D;j++){
            sample[i][j] = data[i*2+j];
        }
    }
    int* label = (int*)calloc(N,sizeof(long int));

    double** now_center  = (double**)calloc(K,sizeof(double*));

    for(i = 0;i < K;i++){
        now_center[i]   = (double*)calloc(D,sizeof(double));
    }

    //cluster using k-means algorithm
    k_means(sample,K,N,D,now_center,label);

    for(i=0;i<K;i++){
        Point center_o(now_center[i][0],now_center[i][1]);
        circle(img_resize,center_o,2,Scalar(0,0,255),2);
    }

    pos.x = (now_center[0][0]+now_center[1][0]+now_center[2][0]+now_center[3][0])/4;
    pos.y = (now_center[0][1]+now_center[1][1]+now_center[2][1]+now_center[3][1])/4;

    circle(img_resize,Point(pos.x,pos.y),4,Scalar(0,255,0),3);
    imshow("vanish_point",img_resize);

    waitKey();

    image = img_resize;
    for(i =0;i<N;i++){
        free(sample[i]);
    }
    for(i =0;i<K;i++){
        free(now_center[i]);
    }
    free(label);

    return pos;
}

Point detect_bottom_line(Mat &image,Point &p_left,Point &p_right){
    double start = getTickCount();

    Mat img_gray,img_equ_hist,img_canny,img_hough;

//    Size dsize;
    vector<Vec4i> lines;
    int tolerance = 30;

//    dsize.height = 400;
//    dsize.width  = 400;

    img_gray.create(image.rows,image.cols,CV_8UC1);

    //resize image
//    resize(image,img_resize,dsize);
 //   imshow("resize",img_resize);

    //apply gaussian blur
//    GaussianBlur(image,img_gaussi,Size(5,5),4,4);
 //   imshow("gaussi",img_gaussi);

    if(image.channels()==3){
        cvtColor(image,img_gray,CV_BGR2GRAY);
   }
    else
        img_gray = image;
//    imshow("gray",img_gray);
//    imwrite("image/gray.jpg",img_gray);

    //histogram equalize
    equalizeHist(img_gray,img_equ_hist);
//    imshow("equa_hist",img_equ_hist);
//    imwrite("image/qua_hist.jpg",img_equ_hist);

    //apply threshold
//    threshold(img_equ_hist,img_thresh,30,255,CV_THRESH_BINARY);
//    imshow("threshold",img_thresh);

    Canny(img_equ_hist,img_canny,40,80);
//    imshow("img_canny",img_canny);
//    imwrite("image/img_canny.jpg",img_canny);

    //apply hough transform
    HoughLinesP(img_canny,lines,1,CV_PI/180,60,10,10);

    img_hough = image;
    //draw the hough result
    vector<Vec4i>::iterator it = lines.begin();
    int line_num = 0;    

    vector<double> data;
    for(;it!=lines.end();it++){
        Vec4i l = *it;
        if(fabs(l[0]-l[2])<tolerance||fabs(l[1]-l[3])<tolerance)
            continue;

        for(int i=0;i<4;i++){
            data.push_back(l[i]);
        }

        //draw the start and end point
        circle(img_hough,Point(l[0],l[1]),2,Scalar(0,0,255));
        circle(img_hough,Point(l[2],l[3]),2,Scalar(0,0,255));

        //draw the line
        line(img_hough,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(255,0,0),1,CV_AA);
        line_num++;
    }

//    imshow("detect_bottom_line",img_hough);
//    imwrite("image/hough.jpg",img_hough);

    if(line_num <= 2) return Point(5,5);

    int i = 0,j = 0;
    long N = line_num;
    int K =4,D = 1;

    double** slope = (double**)calloc(N,sizeof(double*));
    for(i =0;i<N;i++){
        slope[i] = (double*)calloc(D,sizeof(double));
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<D;j++){
            slope[i][j] = (data[i*4+3]-data[i*4+1])/(data[i*4+2]-data[i*4]);
        }
    }

    int* label = (int*)calloc(N,sizeof(long int));
    double** center  = (double**)calloc(K,sizeof(double*));

    for(i = 0;i < K;i++){
        center[i]   = (double*)calloc(D,sizeof(double));
    }

    //cluster using k-means algorithm
    k_means(slope,K,N,D,center,label);

    //define the slope
    double k0 = center[0][0],k1 = center[1][0],k2 = center[2][0],k3 = center[3][0];
    int n0 = 0,n1 = 0,n2=0,n3=0;

    double sum_x_0 =0,sum_y_0 = 0,sum_x_1 = 0,sum_y_1 = 0,sum_x_2 =0,sum_y_2 = 0,sum_x_3 =3,sum_y_3 = 0;
    for(i =0;i<N;i++){
        if(label[i] == 0){
            sum_x_0 += data[i*4]+data[i*4+2];
            sum_y_0 += data[i*4+1]+data[i*4+3];
            n0++;
        }
        else if(label[i] == 1){
            sum_x_1 += data[i*4]+data[i*4+2];
            sum_y_1 += data[i*4+1]+data[i*4+3];
            n1++;
        }
        else if(label[i] == 2){
            sum_x_2 += data[i*4]+data[i*4+2];
            sum_y_2 += data[i*4+1]+data[i*4+3];
            n2++;
        }
        else{
            sum_x_3 += data[i*4]+data[i*4+2];
            sum_y_3 += data[i*4+1]+data[i*4+3];
            n3++;
        }
    }

    sum_x_0 /= (n0*2);
    sum_x_1 /= (n1*2);
    sum_y_0 /= (n0*2);
    sum_y_1 /= (n1*2);

    sum_x_2 /= (n2*2);
    sum_x_3 /= (n3*2);
    sum_y_2 /= (n2*2);
    sum_y_3 /= (n3*2);

    double b0 = sum_y_0 - k0*sum_x_0,b1 = sum_y_1 - k1*sum_x_1,b2 = sum_y_2 - k2*sum_x_2,b3 = sum_y_3 - k3*sum_x_3;

   //cal the left and right points
    p_left.y  = p_right.y = image.rows;
    p_left.x  = (p_left.y-b0)/k0;
    p_right.x = (p_right.y -b1)/k1;

    Point p_left_up,p_right_up;
    p_left_up.y = p_right_up.y = 0;
    p_left_up.x  = (p_left_up.y-b2)/k2;
    p_right_up.x = (p_right_up.y -b3)/k3;

    int temp =  p_right.x;

    p_right.x = p_left.x > p_right.x ? p_left.x:p_right.x;
    p_left.x = p_left.x < temp ? p_left.x:temp;

//    if(p_left.x  < 0)p_left.x = 0;
//    if(p_right.x > image.cols)p_right.x = image.cols;

//    circle(image,p_left,4,Scalar(255,255,0));
//    circle(image,p_right,4,Scalar(255,255,0));

    Point vp_1,vp_2,vp;

    vp_1.x = -1*(b0-b1)/(k0-k1);
    vp_1.y = k0*vp_1.x + b0;

    vp_2.x = -1*(b2-b3)/(k2-k3);
    vp_2.y = k2*vp_2.x + b2;

#if 0
    double hx = 0,tan_theta = 0,theta = 0;
    double dx = 0,dy = 0;

    dx = p_right.x - p_left.x;
    dy = p_left.y  - p_right.y;

    hx = (vp.x*dx-vp.y*dy+p_left.x*dy*dy/dx+p_left.y*dy)/(dy*dy/dx + dx);

    //tan_theta = std::sqrt(((hx - image.cols/2)*(hx - image.cols/2))/((image.rows - vp.y)*(image. rows - vp.y)));
//    if((hx - image.cols/2)/(image.rows - vp.y)>0)
//        tan_theta = std::fabs((hx - image.cols/2)/(image.rows - vp.y));
//    else
//        tan_theta = -1*std::fabs((hx - image.cols/2)/(image.rows - vp.y));

    tan_theta = (vp.x - image.cols/2)*1.0/(image.rows - vp.y);
    int roll  = (p_left.x +p_right.x)/2 - image.cols/2;

    theta = std::atan(tan_theta);

    printf("theta = %lf,roll = %d\n",theta*57.1,roll);
//    printf("hx    = %lf\n",hx);
#endif
    vp.x = vp_1.x/2+vp_2.x/2;
    vp.y = vp_1.y/2+vp_2.y/2;

    Mat img = image;
    if(vp_1.x > image.cols||vp_1.x<0)vp_1.x = image.cols/2;
    if(vp_1.y > image.rows||vp_1.y<0)vp_1.y = image.rows/2;
    vp = vp_1;

    circle(img,Point(vp_1.x,vp_1.y),4,Scalar(0,255,0),3);
//    line(img,vp_1,p_left,Scalar(0,255,255));
//    line(img,vp_1,p_right,Scalar(0,255,255));

//    circle(img,Point(vp_2.x,vp_2.y),4,Scalar(0,0,255),3);
//    line(img,vp_2,p_left_up,Scalar(255,0,255));
//    line(img,vp_2,p_right_up,Scalar(255,0,255));

//    circle(img,Point(vp.x,vp.y),4,Scalar(255,0,0),3);
//    line(img,vp_2,vp_1,Scalar(255,0,0));

//    imwrite("image/vp.jpg",img);


#if 0
    if(vp_1.x<0) vp_1.x = image.cols/2;
    if(vp_1.y<0) vp_1.y = image.rows/2;
    if(vp_1.x>image.cols)vp_1.x = image.cols/2;
    if(vp_1.y>image.rows)vp_1.y = image.rows/2;
#endif

    for(i =0;i<N;i++){
        free(slope[i]);
    }
    for(i =0;i<K;i++){
        free(center[i]);
    }
    free(label);

    double end = getTickCount();

    cout << (end-start)/getTickFrequency()<<endl;
    return vp;
}

//test vanish point in a video
int test_video(int argc,char *argv[]){
    VideoCapture video;
    Mat image_in;
    int time_delay = 20;
    char key = 0;

    Point vp,p_left,p_right;

    if(argc < 2){
        printf("please input the video name\n");
        exit(1);
    }

    video.open(argv[1]);
    if(!video.isOpened()){
        printf("Failed to open video file: %s\n",argv[1]);
        exit(1);
    }

    video >> image_in; printf("step\n");

    vp = detect_bottom_line(image_in,p_left,p_right);

    printf("%d,%d\n",vp.x,vp.y);
    imshow("vanish_point",image_in);
    key = waitKey(time_delay);

    char num[20];
    int i = 0;
    while(key != 27){
        video >> image_in;
        if(image_in.empty())break;

        double t1 = getTickCount();
        vp = detect_bottom_line(image_in,p_left,p_right);
        double t2 = getTickCount();

        sprintf(num,"%d",i);
        string seq(num);

        char vp_str[20];
        sprintf(vp_str,"vp = (%d,%d)",vp.x,vp.y);
        putText(image_in,vp_str,Point(0,20),2,0.5,CV_RGB(25,200,25));

//      printf("time = %lf\n",1000*(t2-t1)/getTickFrequency());
//      printf("image.width = %d\n",image_in.cols);
        printf("%d,%d\n",vp.x,vp.y);
//      printf("p_left.x = %d,p_left.y = %d\n",p_left.x,p_left.y);
//      printf("p_right.x = %d,p_right.y = %d\n",p_right.x,p_right.y);
//      printf("center = %d\n",(p_left.x+p_right.x)/2);

        imshow("vanish_point",image_in);
        imwrite("image/"+seq+".jpg",image_in);
        key = waitKey(50);
        i++;
    }
    return 0;
}
int main(int argc, char *argv[])
{
//   Mat image;
//   Point vp1,vp2,l_p,r_p;

//    image = imread(argv[1]);
//    imshow("origin_pic",image);

//    cout << "width  = " << image.cols << endl;
//    cout << "height = " << image.rows << endl;

//    vp1 = detect_bottom_line(image,l_p,r_p);
//    imshow("vp1",image);
//    waitKey();
//    vp2 = vanish_point(image);
//    imshow("vp2",image);

//    printf("image.width = %d\n",image.cols);
//    printf("p_left.x = %d,p_left.y = %d\n",l_p.x,l_p.y);
//    printf("p_right.x = %d,p_right.y = %d\n",r_p.x,r_p.y);
//    printf("center = %d\n",(l_p.x+r_p.x)/2);
     test_video(argc,argv);

//    printf("vp1.x = %d,vp1.y = %d\n",vp1.x,vp1.y);
//    printf("vp2.x = %d,vp2.y = %d\n",vp2.x,vp2.y);

    return 0;
}

