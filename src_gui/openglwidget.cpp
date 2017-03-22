#include "openglwidget.h"
#include "ui_openglwidget.h"

openGLwidget::openGLwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::openGLwidget)
{
    ui->setupUi(this);
}

openGLwidget::~openGLwidget()
{
    delete ui;
}
