#include "lastwidget.h"
#include "ui_lastwidget.h"

#include <QScreen>
#include <QPushButton>

LastWidget::LastWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LastWidget)
{
    ui->setupUi(this);

    setFixedSize(588,588);

    //居中显示
    QScreen *desk = QGuiApplication::primaryScreen();
    int wd = desk->size().width();
    int ht = desk->size().height();
    this->move((wd-this->width())/2,(ht-this->height())/2);

    connect(ui->lpb0,&QPushButton::clicked,[=](){
        //发一个信号过去
        emit this->back();
    });
}

LastWidget::~LastWidget()
{
    delete ui;
}
