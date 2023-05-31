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
    setFixedSize(2048*0.5,1152*0.5);

    //居中显示
    QScreen *desk = QGuiApplication::primaryScreen();
    int wd = desk->size().width();
    int ht = desk->size().height();
    this->move((wd-this->width())/2,(ht-this->height())/2);
    //设置图标
    ui->pb0->move((width()-ui->pb0->width())*0.5, height() - 220);
    ui->label->move((width()-ui->label->width())*0.5, height()*0.5-115);
    ui->label->setStyleSheet("QLabel{color:white}");

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

void Widget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QPixmap pixMap;

    pixMap.load(":/pic/tec.jpg");
    painter.drawPixmap(0, 0, width(), height(), pixMap);

    /*pixMap.load(":/pic/npu_logo.jpg");
    painter.drawPixmap(0, 0, pixMap.width()*0.3, pixMap.height()*0.3, pixMap);*/
    //painter.drawPixmap((width() - pixMap.width()) * 0.5, 30, pixMap);

}


