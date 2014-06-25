#include "imageviewer.h"

imageViewer::imageViewer(QMainWindow *parent) :
    QMainWindow(parent)
{
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setScaledContents(true);
    imageLabel->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    imageLabel->setAlignment(Qt::AlignCenter);

    scrollArea = new QScrollArea(this);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setWidgetResizable(false);


    setCentralWidget(scrollArea);

    createAction();
    createMenu();
    createContextMenu();

    setWindowTitle(tr("image viewer"));
    resize(400,400);
}

void imageViewer::createAction()
{
    openAction = new QAction(tr("open"),this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction,SIGNAL(triggered()),this,SLOT(open()));

    printAction = new QAction(tr("print"),this);
    printAction->setShortcut(QKeySequence::Print);
    printAction->setEnabled(false);
    connect(printAction,SIGNAL(triggered()),this,SLOT(print()));

    exitAction = new QAction(tr("exit"),this);
    exitAction->setShortcut(QKeySequence::Close);
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

    zoomInAction = new QAction(tr("zoom in"),this);
    zoomInAction->setShortcut(QKeySequence::ZoomIn);
    zoomInAction->setEnabled(false);
    connect(zoomInAction,SIGNAL(triggered()),this,SLOT(zoomIn()));

    zoomOutAction = new QAction(tr("zoom out"),this);
    zoomOutAction->setShortcut(QKeySequence::ZoomOut);
    zoomOutAction->setEnabled(false);
    connect(zoomOutAction,SIGNAL(triggered()),this,SLOT(zoomOut()));

    normalizeAction = new QAction(tr("normalize"),this);
    normalizeAction->setShortcut(QKeySequence(tr("Ctrl+r")));
    normalizeAction->setEnabled(false);
    connect(normalizeAction,SIGNAL(triggered()),this,SLOT(normalize()));

    fitToWindowAction = new QAction(tr("fit to window"),this);
    fitToWindowAction->setShortcut(tr("Ctrl+F"));
    fitToWindowAction->setEnabled(false);
    fitToWindowAction->setCheckable(true);
    connect(fitToWindowAction,SIGNAL(triggered()),this,SLOT(fitToWindow()));

    aboutAction = new QAction(tr("about"),this);
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(about()));

    aboutQtAction = new QAction(tr("about Qt"),this);
    aboutQtAction->setShortcut(QKeySequence(tr("Ctrl+a")));
    connect(aboutQtAction,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
}

void imageViewer::createMenu()
{
    QMenuBar * menubar = new QMenuBar(this);
    menubar->setFixedWidth(width());

    fileMenu = new QMenu(tr("&File"),this);
    fileMenu->addAction(openAction);
    fileMenu->addAction(printAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    viewMenu = new QMenu(tr("&View"),this);
    viewMenu->addAction(zoomInAction);
    viewMenu->addAction(zoomOutAction);
    viewMenu->addAction(normalizeAction);
    viewMenu->addSeparator();
    viewMenu->addAction(fitToWindowAction);

    helpMenu = new QMenu(tr("Help"),this);
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

    menubar->addMenu(fileMenu);
    menubar->addMenu(viewMenu);
    menubar->addMenu(helpMenu);
}

void imageViewer::createContextMenu()
{
    this->addAction(zoomInAction);
    this->addAction(zoomOutAction);
    this->addAction(normalizeAction);
    this->addAction(fitToWindowAction);
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void imageViewer::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("open file"),
                                                    QDir::currentPath());
    if(!fileName.isEmpty()){
        QImage image(fileName);
        if(image.isNull()){
            QErrorMessage *error = new QErrorMessage(this);
            error->showMessage(tr("error:can not load the image"),0);
            return;
        }
        imageLabel->setPixmap(QPixmap::fromImage(image));
        scaleFactor = 1.0;

        printAction->setEnabled(true);
        fitToWindowAction->setEnabled(true);
        updateAction();

        if(!fitToWindowAction->isChecked()){
            imageLabel->adjustSize();
        }
    }
}

void imageViewer::print()
{

}

void imageViewer::zoomIn()
{
    scaleImage(0.8);
}

void imageViewer::zoomOut()
{
    scaleImage(1.25);
}

void imageViewer::normalize()
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void imageViewer::fitToWindow()
{
    scrollArea->setWidgetResizable(fitToWindowAction->isChecked());
    if(!fitToWindowAction->isChecked())
        normalize();
    updateAction();
}

void imageViewer::about()
{

}

void imageViewer::updateAction()
{
    normalizeAction->setEnabled(!fitToWindowAction->isChecked());
    zoomInAction->setEnabled(!fitToWindowAction->isChecked());
    zoomOutAction->setEnabled(!fitToWindowAction->isChecked());
}

void imageViewer::scaleImage(double scale)
{
    scaleFactor *= scale;
    imageLabel->resize(scaleFactor*imageLabel->pixmap()->size());

    adjustScroll(scrollArea->horizontalScrollBar(),scaleFactor);
    adjustScroll(scrollArea->verticalScrollBar(),scaleFactor);
}

void imageViewer::adjustScroll(QScrollBar *scrollBar, double scale)
{
    scrollBar->setValue(scale*scrollBar->value());
}
