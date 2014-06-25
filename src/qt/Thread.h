#ifndef THREAD_H
#define THREAD_H

#include <qthread.h>
#include <qmutex.h>
#include <qsemaphore.h>

class Thread : public QThread
{
    Q_OBJECT
public:
    Thread();

    void stop();
    void setMessage(QString string);
protected:
    virtual void run();
private:
    QMutex mutex;
    volatile bool isStop;
    QString message;
};


class ThreadA : public Thread
{
    Q_OBJECT
public:
    ThreadA();

    void run();
};

class ThreadB : public Thread
{
    Q_OBJECT
public:
    ThreadB();

    void run();
};


#endif // THREAD_H
