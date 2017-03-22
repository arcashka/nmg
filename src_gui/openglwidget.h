#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>

namespace Ui {
class openGLwidget;
}

class openGLwidget : public QWidget
{
    Q_OBJECT

public:
    explicit openGLwidget(QWidget *parent = 0);
    ~openGLwidget();

private:
    Ui::openGLwidget *ui;
};

#endif // OPENGLWIDGET_H
