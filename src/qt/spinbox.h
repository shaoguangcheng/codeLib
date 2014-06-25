#ifndef SPINBOX_H
#define SPINBOX_H

#include <QWidget>

namespace Ui {
class spinbox;
}

class spinbox : public QWidget
{
    Q_OBJECT
    
public:
    explicit spinbox(QWidget *parent = 0);
    ~spinbox();
    
private:
    Ui::spinbox *ui;
};

#endif // SPINBOX_H
