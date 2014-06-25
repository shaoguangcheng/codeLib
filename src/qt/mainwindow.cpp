#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "cv.h"
#include "highgui.h"

#include "analogclock.h"
#include "listWidget.h"

#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    this->setGeometry(100,100,640,480);
    this->setFixedSize(640,480);
    this->setWindowTitle(tr("Qt learning"));

    createButton();
    createAction();
    createMenu();
    createContextMenu();
    createToolbar();
    createStatusBar();
    createWidget();
}

void MainWindow::createWidget()
{
    analogClock *clock;
    clock = new analogClock(this);
    clock->setGeometry(width()-160,height()-250,100,100);
    clock->show();
}

void MainWindow::createButton()
{
    QPushButton *newProcessButton;
    newProcessButton = new QPushButton("&newProcess",this);
    newProcessButton->setGeometry(400,400,150,50);
    newProcessButton->setStatusTip(tr("create a new process"));
    connect(newProcessButton,SIGNAL(clicked()),this,SLOT(executeLs()));

    QPushButton *inputButton;
    inputButton = new QPushButton(tr("&input"),this);
    inputButton->setGeometry(200,400,150,50);
    inputButton->setToolTip(tr("input"));
    inputButton->setStatusTip(tr("input data"));
    connect(inputButton,SIGNAL(clicked()),this,SLOT(input()));
}

void MainWindow::createStatusBar()
{
    statusBar()->clearMessage();
}

void MainWindow::createToolbar()
{
    QToolBar *fileBar = this->addToolBar("file");
    fileBar->setMovable(true);
    fileBar->addAction(openAction);
    fileBar->addAction(saveAction);

}

void MainWindow::createMenu()
{
    QMenuBar *menubar = new QMenuBar(this);//create menubar
    menubar->setBackgroundRole(QPalette::Base);
    menubar->setFixedWidth(this->width());

    QMenu *file = new QMenu(tr("&File"),this);
    menubar->addMenu(file);
    file->addAction(openAction);
    file->addAction(saveAction);
    file->addSeparator();
    file->addAction(closeAction);

    QMenu *option = new QMenu(tr("&Option"),this);
    menubar->addMenu(option);
    option->addAction(chooseColorAction);
    option->addAction(chooseWidgetAction);
}

void MainWindow::createContextMenu()
{
    this->addAction(chooseColorAction);
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createAction()
{
    openAction = new QAction(tr("&open"),this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setToolTip(tr("open files ..."));
    openAction->setStatusTip(tr("open a file..."));
    connect(openAction,SIGNAL(triggered()),this,SLOT(open()));

    saveAction = new QAction(tr("&save"),this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setToolTip(tr("save file"));
    saveAction->setStatusTip(tr("save file"));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(save()));

    closeAction = new QAction(tr("&close"),this);
    closeAction->setShortcut(QKeySequence::Close);
    closeAction->setToolTip(tr("close this programme"));
    closeAction->setStatusTip(tr("close this programme"));
    connect(closeAction,SIGNAL(triggered()),this,SLOT(close()));

    chooseColorAction = new QAction(tr("&color..."),this);
    chooseColorAction->setToolTip(tr("choose a color you want to use"));
    chooseColorAction->setStatusTip(tr("input a color"));
    connect(chooseColorAction,SIGNAL(triggered()),this,SLOT(chooseColor()));

    chooseWidgetAction = new QAction(tr("choose &widget..."),this);
    chooseWidgetAction->setToolTip(tr("choose a widget"));
    chooseWidgetAction->setStatusTip(tr("choose a widget"));
    connect(chooseWidgetAction,SIGNAL(triggered()),this,SLOT(chooseWidget()));
}

#if 1
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);

    painter->setPen(QPen(QBrush(Qt::red),1,Qt::DashDotDotLine,Qt::RoundCap));
    painter->setBrush(QBrush(Qt::yellow));
    painter->drawEllipse(100,100,50,50);

    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->setPen(QPen(QBrush(Qt::red),1,Qt::DashDotDotLine,Qt::RoundCap));
    painter->setBrush(QBrush(Qt::yellow));
    painter->drawEllipse(160,100,50,50);

    if(widgetToDraw == "Line")
        painter->drawLine(100,100,200,200);
    else if(widgetToDraw == "rectangle")
        painter->drawRect(100,100,100,100);

}
#endif

void MainWindow::keyPressEvent(QKeyEvent *event)
{
        if(event->key() == Qt::Key_Escape){
            if(okToClose()){
                this->close();
            }
            else
              //  QMainWindow::keyPressEvent(event);
                event->ignore();
        }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QString msg = QString("pos:%1,%2").arg(QString::number(event->pos().x()),QString::number(event->pos().y()));
    statusBar()->showMessage(msg);
}

void MainWindow::closeEvent(QCloseEvent *event)//close event
{
    if(okToClose()){
        event->accept();
    }
    else{
        event->ignore();
        //QMainWindow::closeEvent(event);
    }
}

bool MainWindow::okToClose()
{

    if(QMessageBox::question(this,tr("close"),tr("do you want to close the window?"),
                          QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
        return true;
    else
        return false;
}

//slots function
void MainWindow::open()
{
    QFileDialog *openFile = new QFileDialog(this,Qt::Dialog);//test open file dialog
    QString fileName = openFile->getOpenFileName(this,
                                                 tr("open file"),
                                                 tr("."),
                                                 tr("all files... *.ui"));
    if(fileName.length()!=0)
        QMessageBox::information(this,
                                 tr("information"),
                                 fileName);

    QMessageBox messgae(QMessageBox::NoIcon,tr("title"),//test message box with construct function method
                        "test",QMessageBox::Yes|QMessageBox::No);
    if(messgae.exec() == QMessageBox::Yes)
        save();
}

void MainWindow::save()
{
    QString fileNameSaved = QFileDialog::getSaveFileName(this, //test save dialog
                                                      tr("save"),
                                                      "/home",
                                                      "image.. *.png");
    cv::Mat pic;
    if(fileNameSaved.length()!=0){
        cv::imwrite(fileNameSaved.toStdString(),pic);
        QMessageBox::information(this,
                                 "save",
                                 fileNameSaved);
    }
}

void MainWindow::input()
{
    bool isOk;
    QString inputString = QInputDialog::getText(this,
                                                tr("input dialog"),
                                                tr("please input data:"),
                                                QLineEdit::Password,
                                                tr("I love Qt"),
                                                &isOk);
    if(isOk){
        QMessageBox::information(this,
                                 tr("hint"),
                                 tr("your input is :")+inputString,
                                 QMessageBox::Ok|QMessageBox::No);
    }
}

void MainWindow::chooseColor()
{
    QColor color = QColorDialog::getColor(Qt::red,this);//test color dialog
    QString message = QString("r:%1,g:%2,b:%3").arg(QString::number(color.red()),
                                                    QString::number(color.green()),
                                                    QString::number(color.blue()));
    QMessageBox::information(this,tr("color"),message);
}

void MainWindow::chooseWidget()
{
    listWidget *list = new listWidget;
    list->show();
}

void MainWindow::executeLs()
{
    QStringList arg;
    arg<< QInputDialog::getText(this,tr("files in path"),
                                 tr("path"));

    process = new QProcess(this);
    process->setProcessChannelMode(QProcess::MergedChannels);
    process->start("ls",arg);
    QStringList *stringList = new QStringList();
    if(process->waitForFinished()){
        if(process->exitCode()!=0){
            QErrorMessage *error = new QErrorMessage(this);
            error->showMessage("error");
            return;
        }
        while(1){
          QByteArray result = process->readLine(100);
          if(result.length()==0)
              break;
            QTextCodec* gbkCodec = QTextCodec::codecForName("GBK");
            QString str = gbkCodec->toUnicode(result);
            stringList->push_back(str);
        }
    }

    QStringListModel *stringListModel = new QStringListModel(this);
    stringListModel->setStringList(*stringList);

    QListView *listView = new QListView(this);
    listView->setModel(stringListModel);
    setCentralWidget(listView);
    listView->show();
}
