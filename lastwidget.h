#ifndef LASTWIDGET_H
#define LASTWIDGET_H

#include <QWidget>

/* 新建的
 * 第2个窗口，检测系统的第2个页面*/

namespace Ui {
class LastWidget;
}

class LastWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LastWidget(QWidget *parent = nullptr);
    ~LastWidget();

signals:
    void back();//定义一个返回上一页的信号

private:
    Ui::LastWidget *ui;
};

#endif // LASTWIDGET_H
