#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <QWidget>

class analogClock : public QWidget
{
    Q_OBJECT
public:
    explicit analogClock(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // ANALOGCLOCK_H
