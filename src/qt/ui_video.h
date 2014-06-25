/********************************************************************************
** Form generated from reading UI file 'video.ui'
**
** Created: Sun Aug 18 16:48:58 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEO_H
#define UI_VIDEO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_video
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *open;
    QSpacerItem *horizontalSpacer;
    QPushButton *play;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pause;

    void setupUi(QWidget *video)
    {
        if (video->objectName().isEmpty())
            video->setObjectName(QString::fromUtf8("video"));
        video->resize(372, 288);
        horizontalLayoutWidget = new QWidget(video);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 250, 361, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        open = new QPushButton(horizontalLayoutWidget);
        open->setObjectName(QString::fromUtf8("open"));

        horizontalLayout->addWidget(open);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        play = new QPushButton(horizontalLayoutWidget);
        play->setObjectName(QString::fromUtf8("play"));

        horizontalLayout->addWidget(play);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pause = new QPushButton(horizontalLayoutWidget);
        pause->setObjectName(QString::fromUtf8("pause"));

        horizontalLayout->addWidget(pause);


        retranslateUi(video);

        QMetaObject::connectSlotsByName(video);
    } // setupUi

    void retranslateUi(QWidget *video)
    {
        video->setWindowTitle(QApplication::translate("video", "Form", 0, QApplication::UnicodeUTF8));
        open->setText(QApplication::translate("video", "open", 0, QApplication::UnicodeUTF8));
        play->setText(QApplication::translate("video", "play", 0, QApplication::UnicodeUTF8));
        pause->setText(QApplication::translate("video", "pause", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class video: public Ui_video {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEO_H
