#include "widget.h"
#include "ui_widget.h"

#include "firstwidget.h"

#include <QPushButton>
#include <QScreen>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setFixedSize(800,600);

    //居中显示
    QScreen *desk = QGuiApplication::primaryScreen();
    int wd = desk->size().width();
    int ht = desk->size().height();
    this->move((wd-this->width())/2,(ht-this->height())/2);

    this->page1 = new FirstWidget;//实例化 欢迎页面类

    //点击进入系统，隐藏欢迎界面，展示page1
    connect(ui->pb0,&QPushButton::clicked,[=](){
        this->hide();
        this->page1->show();
    });

    connect(this->page1,&FirstWidget::back,[=](){
        this->page1->hide();
        this->show();
    });

}

Widget::~Widget()
{
    delete ui;
}


