/********************************************************************************
** Form generated from reading UI file 'firstwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIRSTWIDGET_H
#define UI_FIRSTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FirstWidget
{
public:
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QTextEdit *fileedit;
    QPushButton *fpb2;
    QSpacerItem *verticalSpacer_2;
    QTextEdit *ftext;
    QSpacerItem *verticalSpacer;
    QProgressBar *progressBar;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *fpb3;
    QPushButton *fpb1;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *quitButton;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_4;
    QTreeWidget *treeWidget;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QTextEdit *textEdit;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *selectAll;
    QPushButton *getIMG;
    QPushButton *spb2;
    QPushButton *clearButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *spb0;
    QPushButton *spb1;

    void setupUi(QWidget *FirstWidget)
    {
        if (FirstWidget->objectName().isEmpty())
            FirstWidget->setObjectName("FirstWidget");
        FirstWidget->resize(1200, 712);
        gridLayout = new QGridLayout(FirstWidget);
        gridLayout->setObjectName("gridLayout");
        stackedWidget = new QStackedWidget(FirstWidget);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        verticalLayout = new QVBoxLayout(page);
        verticalLayout->setObjectName("verticalLayout");
        widget_2 = new QWidget(page);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 45));
        widget_2->setMaximumSize(QSize(16777215, 45));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName("horizontalLayout");
        fileedit = new QTextEdit(widget_2);
        fileedit->setObjectName("fileedit");

        horizontalLayout->addWidget(fileedit);

        fpb2 = new QPushButton(widget_2);
        fpb2->setObjectName("fpb2");

        horizontalLayout->addWidget(fpb2);


        verticalLayout->addWidget(widget_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        ftext = new QTextEdit(page);
        ftext->setObjectName("ftext");
        ftext->setMinimumSize(QSize(0, 0));
        ftext->setMaximumSize(QSize(5000, 16777215));

        verticalLayout->addWidget(ftext);

        verticalSpacer = new QSpacerItem(2, 2, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        progressBar = new QProgressBar(page);
        progressBar->setObjectName("progressBar");
        progressBar->setMinimumSize(QSize(0, 30));
        progressBar->setMaximumSize(QSize(16777215, 30));
        progressBar->setValue(0);
        progressBar->setTextVisible(true);
        progressBar->setOrientation(Qt::Horizontal);
        progressBar->setInvertedAppearance(false);

        verticalLayout->addWidget(progressBar);

        widget = new QWidget(page);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 50));
        widget->setMaximumSize(QSize(16777215, 50));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        fpb3 = new QPushButton(widget);
        fpb3->setObjectName("fpb3");

        horizontalLayout_2->addWidget(fpb3);

        fpb1 = new QPushButton(widget);
        fpb1->setObjectName("fpb1");

        horizontalLayout_2->addWidget(fpb1);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        quitButton = new QPushButton(widget);
        quitButton->setObjectName("quitButton");

        horizontalLayout_2->addWidget(quitButton);


        verticalLayout->addWidget(widget);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(4, 2);
        verticalLayout->setStretch(5, 1);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        verticalLayout_3 = new QVBoxLayout(page_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        widget_5 = new QWidget(page_2);
        widget_5->setObjectName("widget_5");
        horizontalLayout_4 = new QHBoxLayout(widget_5);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(10, 5, 10, 5);
        treeWidget = new QTreeWidget(widget_5);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setMinimumSize(QSize(0, 606));
        treeWidget->setMaximumSize(QSize(256, 606));
        treeWidget->setLineWidth(0);

        horizontalLayout_4->addWidget(treeWidget);

        widget_4 = new QWidget(widget_5);
        widget_4->setObjectName("widget_4");
        widget_4->setMinimumSize(QSize(0, 620));
        verticalLayout_2 = new QVBoxLayout(widget_4);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(9, 9, -1, -1);
        label = new QLabel(widget_4);
        label->setObjectName("label");
        label->setMinimumSize(QSize(950, 480));
        label->setMaximumSize(QSize(950, 480));
        label->setTextFormat(Qt::PlainText);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label->setMargin(0);

        verticalLayout_2->addWidget(label, 0, Qt::AlignHCenter|Qt::AlignTop);

        textEdit = new QTextEdit(widget_4);
        textEdit->setObjectName("textEdit");
        textEdit->setMinimumSize(QSize(930, 120));
        textEdit->setMaximumSize(QSize(930, 120));

        verticalLayout_2->addWidget(textEdit, 0, Qt::AlignHCenter|Qt::AlignBottom);


        horizontalLayout_4->addWidget(widget_4);

        horizontalLayout_4->setStretch(1, 4);

        verticalLayout_3->addWidget(widget_5);

        widget_3 = new QWidget(page_2);
        widget_3->setObjectName("widget_3");
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_2 = new QSpacerItem(8, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        selectAll = new QPushButton(widget_3);
        selectAll->setObjectName("selectAll");

        horizontalLayout_3->addWidget(selectAll);

        getIMG = new QPushButton(widget_3);
        getIMG->setObjectName("getIMG");

        horizontalLayout_3->addWidget(getIMG);

        spb2 = new QPushButton(widget_3);
        spb2->setObjectName("spb2");

        horizontalLayout_3->addWidget(spb2);

        clearButton = new QPushButton(widget_3);
        clearButton->setObjectName("clearButton");

        horizontalLayout_3->addWidget(clearButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        spb0 = new QPushButton(widget_3);
        spb0->setObjectName("spb0");

        horizontalLayout_3->addWidget(spb0);

        spb1 = new QPushButton(widget_3);
        spb1->setObjectName("spb1");

        horizontalLayout_3->addWidget(spb1);

        getIMG->raise();
        spb2->raise();
        spb0->raise();
        spb1->raise();
        selectAll->raise();
        clearButton->raise();

        verticalLayout_3->addWidget(widget_3);

        stackedWidget->addWidget(page_2);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);


        retranslateUi(FirstWidget);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(FirstWidget);
    } // setupUi

    void retranslateUi(QWidget *FirstWidget)
    {
        FirstWidget->setWindowTitle(QCoreApplication::translate("FirstWidget", "\347\241\254\344\273\266\350\256\276\350\256\241\345\217\257\346\265\213\346\200\247\345\222\214\345\256\211\345\205\250\346\200\247\345\217\257\350\247\206\345\214\226\345\210\206\346\236\220\347\263\273\347\273\237", nullptr));
        fpb2->setText(QCoreApplication::translate("FirstWidget", "\351\200\211\346\213\251Verilog\346\226\207\344\273\266", nullptr));
        fpb3->setText(QCoreApplication::translate("FirstWidget", "\344\270\200\351\224\256\350\247\243\346\236\220", nullptr));
        fpb1->setText(QCoreApplication::translate("FirstWidget", "\345\217\257\350\247\206\345\214\226\345\210\206\346\236\220", nullptr));
        quitButton->setText(QCoreApplication::translate("FirstWidget", "\351\200\200\345\207\272", nullptr));
        label->setText(QString());
        textEdit->setHtml(QCoreApplication::translate("FirstWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\276\223\345\207\272\357\274\232</p></body></html>", nullptr));
        selectAll->setText(QCoreApplication::translate("FirstWidget", "\345\205\250\351\200\211", nullptr));
        getIMG->setText(QCoreApplication::translate("FirstWidget", "\347\224\237\346\210\220\345\233\276\345\203\217", nullptr));
        spb2->setText(QCoreApplication::translate("FirstWidget", "\344\277\235\345\255\230\345\233\276\345\203\217", nullptr));
        clearButton->setText(QCoreApplication::translate("FirstWidget", "\346\270\205\347\251\272", nullptr));
        spb0->setText(QCoreApplication::translate("FirstWidget", "\350\277\224\345\233\236", nullptr));
        spb1->setText(QCoreApplication::translate("FirstWidget", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FirstWidget: public Ui_FirstWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRSTWIDGET_H
