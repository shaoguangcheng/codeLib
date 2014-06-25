#ifndef QIMAGEMAT_H
#define QIMAGEMAT_H

#include <QWidget>

#include <string>

#include "cv.h"
#include "highgui.h"
using namespace cv;

class QMat : public QWidget
{
    Q_OBJECT
public:
     QMat(const Mat &image,QWidget *parent = 0);
     QMat(const QImage &image,QWidget *parent = 0);

     ~QMat(){delete qImage;delete mImage;}

    inline Mat toMat(){return *mImage;}
    inline QImage toQImage(){return *qImage;}

    void paintEvent(QPaintEvent *event);
    
private:
    QImage *qImage;
    Mat    *mImage;
};

 Mat QImage2Mat(const QImage &image);
 QImage Mat2QImage(const Mat &image);

class QVideo : QWidget
{
    Q_OBJECT
public:
    QVideo(QWidget *parent = 0);
    QVideo(const std::string & videoName,QWidget *parent = 0);

    void paintEvent(QPaintEvent *event);

public slots:
    void play();
    void pause();
    void open();

private:
    VideoCapture *video;
    QImage nextImage;
    QTimer *timer;
    Mat image;

    int frames;
    int width;
    int height;
    int fps;

    void getNextIMage();
    void setupUi();
};

#endif // QIMAGE2MAT_H
