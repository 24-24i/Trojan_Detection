#include "titlewidget.h"
#include "ui_titlewidget.h"

#include <QDebug>

titlewidget::titlewidget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::titlewidget)
{
    ui->setupUi(this);
    setStyleSheet("border:1px solid red;");
}

titlewidget::~titlewidget()
{
    delete ui;
}

#include "QDockWidget"
#include "QDesktopServices"

void titlewidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    QDockWidget *w = (QDockWidget *)this->parentWidget();
    qDebug() << w->isFloating();

    if(w->isFloating()){
        static bool max = false;
        static QRect location = w->geometry();

        if (max) {
            w->setGeometry(location);

        } else {
            location = w->geometry();
            //w->setGeometry(qApp->desktop()->availableGeometry(w->geometry().center()));
        }
        qDebug() << "double clicked" <<max;
        max = !max;
    }
}
