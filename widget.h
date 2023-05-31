#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "firstwidget.h"//下一页 也就是系统第一页 对应类的头文件


/*创建项目就有的，运行后第一个出现的窗口，是欢迎窗口
 * 第0个窗口*/

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    FirstWidget *page1 = NULL;//用来保存 第1页实例化对象的地址

    void paintEvent(QPaintEvent* event);//绘制第0页图像

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
