#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QtGui>

class imageViewer : public QMainWindow
{
    Q_OBJECT
public:
    explicit imageViewer(QMainWindow *parent = 0);

signals:

private slots:
    void open();
    void print();
    void zoomIn();
    void zoomOut();
    void normalize();
    void fitToWindow();
    void about();

//    void closeEvent(QCloseEvent *);

private:
    void createAction();
    void createMenu();
    void createContextMenu();

    void scaleImage(double scale);
    void adjustScroll(QScrollBar *scrollBar,double scale);
    bool okToClose();
    void updateAction();

    QScrollArea *scrollArea;
    QLabel     *imageLabel;
    double     scaleFactor;

    QAction *openAction;
    QAction *printAction;
    QAction *exitAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *fitToWindowAction;
    QAction *normalizeAction;
    QAction *aboutAction;
    QAction *aboutQtAction;

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
};

#endif // IMAGEVIEWER_H
