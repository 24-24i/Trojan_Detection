#include "widget.h"
#include "ui_widget.h"

#include "firstwidget.h"

#include <QPushButton>
#include <QScreen>

Widget::Widget(QWidget *parent)
        : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    setFixedSize(1200, 700);
    setWindowIcon(QIcon("./pic/logo.jpg"));

    //居中显示
    QScreen *desk = QGuiApplication::primaryScreen();
    int wd = desk->size().width();
    int ht = desk->size().height();
    this->move((wd - this->width()) / 2, (ht - this->height()) / 2);
    //设置图标
    // ui->pb0->move((width()-ui->pb0->width())*0.5, height() - 220);
    ui->label->move((width() - ui->label->width()) * 0.5, height() * 0.5 - 115);
    ui->label->setStyleSheet("QLabel{color:white}");

    this->page1 = new FirstWidget;//实例化 欢迎页面

    //创建一个定时器对象
    QTimer *timer = new QTimer(this);
    //设置定时器为单次触发
    timer->setSingleShot(true);
    //连接定时器的timeout信号到槽函数
    connect(timer, &QTimer::timeout, [=]() {
        this->hide();
        this->page1->show();
    });
    //启动定时器，设置时间间隔
    timer->start(2500);

}

Widget::~Widget() {
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap pixMap;

    pixMap.load(":/pic/tec.jpg");
    painter.drawPixmap(0, 0, width(), height(), pixMap);
}


