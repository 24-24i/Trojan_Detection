#include "firstwidget.h"
#include "ui_firstwidget.h"
#include "titlewidget.h"
#include <QScreen>
#include <QPushButton>
#include <qstackedwidget.h>
#include <QMessageBox>
#include <QFileDialog>
#include <QSaveFile>
#include <QPixmap>

FirstWidget::FirstWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FirstWidget)
{
    ui->setupUi(this);

    //0.页面世界效果调整
    setFixedSize(800,600);
    //居中显示
    QScreen *desk = QGuiApplication::primaryScreen();
    int wd = desk->size().width();
    int ht = desk->size().height();
    this->move((wd-this->width())/2,(ht-this->height())/2);
    //默认情况下显示0号页
    ui->stackedWidget->setCurrentIndex(0);
    //布局控件参数调整
    ui->verticalSpacer->changeSize(4,4);//弹簧长度


//    //ui->dockWidget->setTitleBarWidget( NULL );
//    //ui->dockWidget->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);

//    //QDockWidget *dw = new QDockWidget;
//    const QString name = "飞行轨迹";
//    ui->dockWidget->setObjectName(name);
//    ui->dockWidget->setWindowTitle(name);
//    ui->dockWidget->setStyleSheet("border:1px solid blue;");
//    ui->dockWidget->setMinimumWidth(50);
//    ui->dockWidget->setMinimumHeight(50);
//    ui->dockWidget->setWidget(new QTextEdit);
//    ui->dockWidget->setWindowFlags(Qt::FramelessWindowHint |Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);


//    QWidget *_titleWidget = new titlewidget;
//    ui->dockWidget->setTitleBarWidget(_titleWidget);

/*stackwidget0*/

    //1.页面跳转实现
    connect(ui->fpb0,&QPushButton::clicked,[=](){
        //发一个信号过去
        emit this->back();
    });
    connect(ui->fpb1,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });

    //2.进度条相关操作
    analyzeTimer = new QTimer(this);//初始化定时器
    analyzeTimer->setInterval(100);//设置间隔
    //进度条开始和一键解析按钮关联
    connect(ui->fpb3,&QPushButton::clicked,this,&FirstWidget::onfpb3begin);
    //时间到后 调用超时函数，弹出提示框
    connect(analyzeTimer,&QTimer::timeout,this,&FirstWidget::onfpb3timeout);

    //3.文件选择并展示
    connect(ui->fpb2,&QPushButton::clicked,[=](){
        //选择文件对话框
        QString path = QFileDialog::getOpenFileName(this,"打开文件");
        //写路径
        ui->fileedit->setText(path);

        //读取内容 放到text框里
        QFile file(path);
        file.open(QIODevice::ReadOnly);
        QByteArray array = file.readAll();
        ui->ftext->setText(array);
    });

/*stackwidget1*/
    //1.按钮功能实现
    connect(ui->spb0,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    //退出按钮实现
    connect(ui->spb1,&QPushButton::clicked,[=](){
        this->close();
    });
    //保存图像
    connect(ui->spb2,&QPushButton::clicked,this,&FirstWidget::savefile);

    //2.图像模块
    //ui->label->setPixmap(QPixmap(":/pic/npu_logo.jpg"));

    //3.数据模块
    //4.左侧下拉目录（treewidget+信号槽连接）
    //设置水平头
    ui->treeWidget->setHeaderLabels(QStringList()<< "Hierarchy");
    //顶层结点设置,先定义，再放到ui里
    QTreeWidgetItem * layer1 = new QTreeWidgetItem(QStringList()<<"aes_T1000");
    ui->treeWidget->addTopLevelItem(layer1);
    //追加子节点
    QStringList m1;
    QStringList m2;
    QStringList m3;
    QStringList m4;
    QStringList m5;
    QStringList m6;
    QStringList m7;
    QStringList m8;
    QStringList m9;
    QStringList m10;
    QStringList m11;
    QStringList m12;
    QStringList m13;

    m1 << "aes_128";
    m2 << "expand_key_128";
    m3 << "final_round";
    m4 << "lfsr_counter";
    m5 << "one_round";
    m6 << "S";
    m7 << "S4";
    m8 << "T";
    m9 << "table_lookup";
    m10 << "top";
    m11 << "Trojan_Trigger";
    m12 << "TSC";
    m13 << "XS";

    QTreeWidgetItem * l1 = new QTreeWidgetItem(m1);
    layer1->addChild(l1);
    QTreeWidgetItem * l2 = new QTreeWidgetItem(m2);
    layer1->addChild(l2);
    QTreeWidgetItem * l3 = new QTreeWidgetItem(m3);
    layer1->addChild(l3);
    QTreeWidgetItem * l4 = new QTreeWidgetItem(m4);
    layer1->addChild(l4);
    QTreeWidgetItem * l5 = new QTreeWidgetItem(m5);
    layer1->addChild(l5);
    QTreeWidgetItem * l6 = new QTreeWidgetItem(m6);
    layer1->addChild(l6);
    QTreeWidgetItem * l7 = new QTreeWidgetItem(m7);
    layer1->addChild(l7);
    QTreeWidgetItem * l8 = new QTreeWidgetItem(m8);
    layer1->addChild(l8);
    QTreeWidgetItem * l9 = new QTreeWidgetItem(m9);
    layer1->addChild(l9);
    QTreeWidgetItem * l10 = new QTreeWidgetItem(m10);
    layer1->addChild(l10);
    QTreeWidgetItem * l11 = new QTreeWidgetItem(m11);
    layer1->addChild(l11);
    QTreeWidgetItem * l12 = new QTreeWidgetItem(m12);
    layer1->addChild(l12);
    QTreeWidgetItem * l13 = new QTreeWidgetItem(m13);
    layer1->addChild(l13);
}

FirstWidget::~FirstWidget()
{
    delete ui;
}

void FirstWidget::onfpb3begin()//开始函数
{
    analyzeTimer->start();

}

void FirstWidget::onfpb3timeout()//超时函数
{

    int currentvalue = ui->progressBar->value();
    if(currentvalue >= ui->progressBar->maximum()){
        analyzeTimer->stop();
        QMessageBox::information(this,"Information","模块化解析完成\n得到下列模块：\naes_128\nexpand_key_128\nfinal_round\n"
        "lfsr_counter\none_round\nS\nS4\nT\ntable_lookup\ntop\nTrojan_Trigger\nTSC\nXS");
//        ms.setWindowTitle(tr("Information"));
//        ms.setInformativeText(tr("模块化解析完成\n得到下列模块：\naes_128\nexpand_key_128\nfinal_round\n"
//        "lfsr_counter\none_round\nS\nS4\nT\ntable_lookup\ntop\nTrojan_Trigger\nTSC\nXS"));
//        ms.resize(200,500);
//        ms.show();
    }
    else{
        ui->progressBar->setValue(ui->progressBar->value() + 1);
    }
}

void FirstWidget::savefile()
{
    //另存为
    QString filename1 = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Images (*.png *.bmp *.jpg)")); //选择路径
    QScreen *screen = QGuiApplication::primaryScreen();
    screen->grabWindow(ui->label->winId()).save(filename1);
}
