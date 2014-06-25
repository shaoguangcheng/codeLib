#include "qimagemat.h"

#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QEvent>

#include <cassert>

QMat::QMat(const Mat &image,QWidget *parent)
{
    assert(image.data != NULL);

    QWidget::setParent(parent);

    Mat imageTemp = image;
    mImage = new Mat(image);

    cvtColor(image,imageTemp,CV_BGR2RGB);

    qImage = new QImage(imageTemp.data,imageTemp.cols,imageTemp.rows,imageTemp.step,QImage::Format_RGB888);
}

QMat::QMat(const QImage &image,QWidget *parent)
{
    assert(image.bits() != NULL);

    QWidget::setParent(parent);

    qImage = new QImage(image);

    if(!image.isGrayscale()){
        Mat *m = new Mat(qImage->height(),qImage->width(),
                         CV_8UC4,qImage->bits(),
                         qImage->bytesPerLine());
        mImage = new Mat(qImage->height(),qImage->width(),CV_8UC3);
        int fromTo[] = {0,0, 1,1, 2,2};
        mixChannels(m,1,mImage,1,fromTo,3);
    }else{
        mImage = new Mat(qImage->height(),qImage->width(),
                         CV_8UC1,qImage->bits(),
                         qImage->bytesPerLine());
    }

}


void QMat::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap::fromImage(*qImage));
}

Mat QImage2Mat(const QImage &image)
{
    QMat m(image);
    return m.toMat();
}

QImage Mat2QImage(const Mat &image)
{
    QMat m(image);
    return m.toQImage();
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
QVideo::QVideo(QWidget *parent):
    QWidget(parent)
{
    setWindowTitle(tr("video"));
    width = 400;
    height = 300;

    setVisible(true);
    resize(width,height);

    setupUi();

    video = new VideoCapture;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
}

QVideo::QVideo(const std::string &videoName,QWidget *parent)
{
    QWidget::setParent(parent);

    video = new VideoCapture;
    video->open(videoName);
    if(!video->isOpened()){
        width = 400;
        height = 300;
    }else{
        frames = video->get(CV_CAP_PROP_FRAME_COUNT);
        width  = video->get(CV_CAP_PROP_FRAME_WIDTH);
        height = video->get(CV_CAP_PROP_FRAME_HEIGHT);
        fps    = video->get(CV_CAP_PROP_FPS);
        image.create(width,height,CV_8UC3);
    }

    setVisible(true);
    resize(width,height);

    setupUi();

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
}

void QVideo::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    getNextIMage();
    painter.drawImage(0,0,nextImage);
}

void QVideo::play()
{
    timer->start(50);
}

void QVideo::getNextIMage()
{
    *video >> image;
    if(image.empty())
        timer->stop();
    else
        nextImage = Mat2QImage(image);
}

void QVideo::pause()
{
    timer->stop();
}


void QVideo::open()
{
    QFileDialog *fileDialog = new QFileDialog(this,Qt::Dialog);

    std::string videoName = fileDialog->getOpenFileName(this,tr("open video"),
                                            tr("."),
                                            tr("*.rmvb *.mkv *.avi *.mp4")).toStdString();
    video->~VideoCapture();
    video = new VideoCapture;
    video->open(videoName);
    assert(video->isOpened());

    frames = video->get(CV_CAP_PROP_FRAME_COUNT);
    width  = video->get(CV_CAP_PROP_FRAME_WIDTH);
    height = video->get(CV_CAP_PROP_FRAME_HEIGHT);
    fps    = video->get(CV_CAP_PROP_FPS);

    resize(width,height);
//    updateGeometry();
    image.create(width,height,CV_8UC3);
    play();
}

void QVideo::setupUi()
{
    QPushButton *playButton = new QPushButton(tr("play"),this);
    QPushButton *pauseButton = new QPushButton(tr("pause"),this);
    QPushButton *openButton  = new QPushButton(tr("open"),this);

    connect(openButton,SIGNAL(clicked()),this,SLOT(open()));
    connect(playButton,SIGNAL(clicked()),this,SLOT(play()));
    connect(pauseButton,SIGNAL(clicked()),this,SLOT(pause()));
}
