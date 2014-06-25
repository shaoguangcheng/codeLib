#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QDialog>
#include <qsemaphore.h>

#include "ui_testThread.h"
#include "Thread.h"



class testThread : public QDialog ,public Ui::testThread
{
    Q_OBJECT
public:
    explicit testThread(QWidget *parent = 0);

    void closeEvent(QCloseEvent *);
private slots:
    void threadAStartOrStop();
    void threadBStartOrStop();

private:
    int value;

    ThreadA *threadA;
    ThreadB *threadB;

    void setMessage();
};

#endif // TESTTHREAD_H
