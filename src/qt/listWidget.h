#ifndef WIDGETLIST_H
#define WIDGETLIST_H

#include <QWidget>
#include <QtGui/qpushbutton.h>
#include <QtGui/qlabel.h>
#include <QtGui/qlistwidget.h>
#include <QtGui/QListWidgetItem>

class listWidget : public QWidget
{
    Q_OBJECT
public:
    explicit listWidget(QWidget *parent = 0);
private:
    QLabel      *label;
    QPushButton *chooseButton;
    QListWidget *listWid;
signals:
    bool isClosed();

public slots:
    QString returnWidgetName();
};

#endif // WIDGETLIST_H
