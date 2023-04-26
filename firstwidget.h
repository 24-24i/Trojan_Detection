#ifndef FIRSTWIDGET_H
#define FIRSTWIDGET_H

#include <QWidget>

#include <QTimer>
/* 新建的
 * 第1个页面：检测系统的第一个页面*/

namespace Ui {
class FirstWidget;
}

class FirstWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FirstWidget(QWidget *parent = nullptr);
    ~FirstWidget();

signals:
    void back();//定义一个返回上一页的信号

private slots:
    void onfpb3begin();//点击一键解析的槽函数
    void onfpb3timeout();
    void savefile();//保存图像

private:
    Ui::FirstWidget *ui;

    QTimer* analyzeTimer;//定时器
};

#endif // FIRSTWIDGET_H
