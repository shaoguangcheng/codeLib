#include <QApplication>
#include <paths.h>

#include "mainwindow.h"
#include "analogclock.h"
#include "imageviewer.h"
#include "testthread.h"
//#include "tetrixwindow.h"
#include "qimagemat.h"
#include "listWidget.h"

#include <sys/queue.h>

#include <highgui.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    imageViewer *view = new imageViewer;
    view->show();

    analogClock *clock = new analogClock;
 //   QLabel *label = new QLabel("mdi");

    clock->setFixedSize(200,200);
//    label->setFixedSize(1000,1000);

    QMdiArea *mdiArea = new QMdiArea;
    mdiArea->setFixedSize(400,400);
    mdiArea->addSubWindow(clock);
    mdiArea->show();

    listWidget * list = new listWidget;
    list->show();

//    testThread test;
 //   test.show();

//    TetrixWindow window;
//    window.show();

//    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));


#if 0
    QImage *image = new QImage("/home/cheng/Downloads/image/image1.jpg");
    assert(!image->isNull());

    QMat *m = new QMat(*image);
    m->resize(image->width(),image->height());
    m->show();
#endif

    //test transform mat to QImage
#if 0
    Mat image = imread("/home/cheng/Downloads/image/image1.jpg");
    QMat *m = new QMat(image);
    m->resize(image.cols,image.rows);
    m->show();
#endif

#if 1
    QVideo video("/home/cheng/disk-others/torrent/The.Great.Gatsby.mkv");
    video.play();
#endif

    return app.exec();
}
