#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected :
    void closeEvent(QCloseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    
private:
    Ui::MainWindow *ui;

    QAction     *openAction;
    QAction     *saveAction;
    QAction     *closeAction;
    QAction     *chooseColorAction;
    QAction     *chooseWidgetAction;

    void initUI();
    void createAction();
    void createMenu();
    void createContextMenu();
    void createToolbar();
    void createStatusBar();
    void createButton();

    void createWidget();

    bool okToClose();

    QString widgetToDraw;

    QProcess *process;
 private slots:
    void open();
    void save();
    void input();
    void chooseColor();
    void chooseWidget();

    void executeLs();
};

#endif // MAINWINDOW_H
