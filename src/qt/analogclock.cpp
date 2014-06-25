#include "analogclock.h"
#include "QtGui"

analogClock::analogClock(QWidget *parent) :
    QWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(1000);

    this->setWindowTitle(tr("analog clock"));
    this->setBackgroundRole(QPalette::Background);
    this->setAutoFillBackground(true);
    this->resize(200,200);
}

void analogClock::paintEvent(QPaintEvent *event)
{
    const QPoint hourHand[3] = {
        QPoint(7,8),
        QPoint(-7,8),
        QPoint(0,-40)
    };
    const QPoint minHand[3] = {
        QPoint(7,8),
        QPoint(-7,8),
        QPoint(0,-60)
    };
    const QPoint secHand[3] = {
        QPoint(7,8),
        QPoint(-7,8),
        QPoint(0,-85)
    };

    QColor hourHandColor(127,0,127);
    QColor minHandColor(0,127,127,200);
    QColor secHandColor(90,17,127,100);

    int side = qMin(width(),height());
    QTime time = QTime::currentTime();

    QTransform transform;
    transform.translate(width()/2,height()/2);
    transform.scale(side/200.0,side/200.0);

    QPainter *painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setWorldTransform(transform);

    painter->setPen(Qt::NoPen);
    painter->setBrush(hourHandColor);

    painter->save();
    painter->rotate(30*(time.hour()+time.minute()/60));
    painter->drawConvexPolygon(hourHand,3);
    painter->restore();

    painter->setPen(hourHandColor);
    for(int i=0;i<12;i++){
        painter->drawLine(88,0,96,0);
        if(i<=9)
            painter->drawText(80,0,QString::number(i+3));
        else
            painter->drawText(80,0,QString::number(i-9));
        painter->rotate(30.0);
    }

    painter->setPen(Qt::NoPen);
    painter->setBrush(minHandColor);

    painter->save();
    painter->rotate(6.0*(time.minute()+time.second()/60));
    painter->drawConvexPolygon(minHand,3);
    painter->restore();

    painter->setPen(minHandColor);
    for(int j=0;j<60;j++){
        if(j%5 != 0){
            painter->drawLine(92,0,96,0);
        }
        painter->rotate(6.0);
    }

    painter->setPen(Qt::NoPen);
    painter->setBrush(secHandColor);

    painter->save();
    painter->rotate(6.0*time.second());
    painter->drawConvexPolygon(secHand,3);
    painter->restore();
}
