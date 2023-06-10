/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *label;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(1200, 800);
        label = new QLabel(Widget);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 330, 1231, 101));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267")});
        font.setPointSize(38);
        font.setStrikeOut(false);
        label->setFont(font);
        label->setFrameShadow(QFrame::Plain);
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "\347\241\254\344\273\266\350\256\276\350\256\241\345\217\257\346\265\213\346\200\247\345\222\214\345\256\211\345\205\250\346\200\247\345\217\257\350\247\206\345\214\226\345\210\206\346\236\220\347\263\273\347\273\237", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\347\241\254\344\273\266\350\256\276\350\256\241\345\217\257\346\265\213\346\200\247\345\222\214\345\256\211\345\205\250\346\200\247\345\217\257\350\247\206\345\214\226\345\210\206\346\236\220\347\263\273\347\273\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
