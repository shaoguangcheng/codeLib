#include "spinbox.h"
#include "ui_spinbox.h"

spinbox::spinbox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::spinbox)
{
    ui->setupUi(this);
}

spinbox::~spinbox()
{
    delete ui;
}
