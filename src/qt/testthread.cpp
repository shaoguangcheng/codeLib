#include "testthread.h"

testThread::testThread(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    lineEdit->setText("0");
    lineEdit->setAlignment(Qt::AlignCenter);

    value = 0;
    threadA = new ThreadA();
    threadB = new ThreadB();

    connect(this->threadAButton,SIGNAL(clicked()),this,SLOT(threadAStartOrStop()));
    connect(this->threadBButton,SIGNAL(clicked()),this,SLOT(threadBStartOrStop()));
}

void testThread::threadAStartOrStop()
{
    if(threadA->isRunning()){
        threadA->stop();
        threadAButton->setText(tr("startA"));
    }
    else{
        threadA->start();
        threadAButton->setText(tr("stopA"));
    }
    setMessage();
}

void testThread::threadBStartOrStop()
{
    if(threadB->isRunning()){
        threadB->stop();
        threadBButton->setText(tr("startB"));
    }
    else{
        threadB->start();
        threadBButton->setText(tr("stopB"));
    }

    setMessage();
}

void testThread::setMessage()
{
    value++;
    QString string;
    lineEdit->setText(string.number(double(value)));
}

void testThread::closeEvent(QCloseEvent *event)
{
    threadA->stop();
    threadB->stop();
}
