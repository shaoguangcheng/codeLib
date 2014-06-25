#include "Thread.h"

Thread::Thread()
{
    isStop = false;
}

void Thread::stop()
{
    mutex.lock();
    isStop = true;
    mutex.unlock();
}

void Thread::setMessage(QString string)
{
    message = string;
}

void Thread::run()
{
    qDebug(message.toStdString().c_str());
    isStop = false;
}

QSemaphore semA(1);
QSemaphore semB(0);

ThreadA::ThreadA()
{
}

void ThreadA::run()
{
    forever{
        semA.acquire();
        setMessage(tr("A"));
        Thread::run();
        semB.release();
    }
}

ThreadB::ThreadB()
{
}

void ThreadB::run()
{
    forever{
        semB.acquire();
        setMessage(tr("B"));
        Thread::run();
        semA.release();
    }
}
