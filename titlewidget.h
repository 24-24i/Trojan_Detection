#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class titlewidget;
}

class titlewidget : public QWidget
{
    Q_OBJECT

public:
    explicit titlewidget(QWidget *parent = nullptr);
    ~titlewidget();

    QSize sizeHint() const override { return QSize(40, 40); }

    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    Ui::titlewidget *ui;
};

#endif // TITLEWIDGET_H
