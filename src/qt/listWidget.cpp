#include "listWidget.h"

#include <QtGui/QHBoxLayout>

listWidget::listWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setGeometry(100,100,400,300);
    label = new QLabel(this);
    label->setFixedWidth(70);

    listWid = new QListWidget(this);
    QListWidgetItem *item1 = new QListWidgetItem(QIcon(tr(":icons/line.bmp")),tr("Line"));
    QListWidgetItem *item2 = new QListWidgetItem(QIcon(tr(":icons/rectangle.bmp")),tr("rectangle"));

    listWid->addItem(item1);
    listWid->addItem(item2);
    connect(listWid,SIGNAL(currentTextChanged(QString)),label,SLOT(setText(QString)));

    QHBoxLayout *HLayoutBox = new QHBoxLayout;
    HLayoutBox->addWidget(label);
    HLayoutBox->addWidget(listWid);

    chooseButton = new QPushButton(tr("choose"),this);
    connect(chooseButton,SIGNAL(clicked()),this,SLOT(returnWidgetName()));

    QVBoxLayout *VBoxLayout = new QVBoxLayout(this);
    VBoxLayout->addLayout(HLayoutBox);
    VBoxLayout->addWidget(chooseButton,0,Qt::AlignCenter);
}

QString listWidget::returnWidgetName()
{
    QString str = label->text();
    this->close();
    return str;
}
