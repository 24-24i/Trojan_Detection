#ifndef FIRSTWIDGET_H
#define FIRSTWIDGET_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTimer>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>

#include <vector>

/* 新建的
 * 第1个页面：检测系统的第一个页面*/

namespace Ui {
    class FirstWidget;
}

class FirstWidget : public QWidget {
Q_OBJECT

public:
    explicit FirstWidget(QWidget *parent = nullptr);

    ~FirstWidget();

    void clear();

    void paintEvent(QPaintEvent *event);//绘制第1页图像

signals:

    void back();//定义一个返回上一页的信号

    // 将所选文件列表中的数据提取出来
    std::vector<double> ExtractData(const QStringList &statFilePathList);


private slots:

    void onfpb3begin();//点击一键解析的槽函数
    void onfpb3timeout();

    void savefile();//保存图像

private:
    Ui::FirstWidget *ui;

    QTimer *analyzeTimer;//定时器
    QString folderPath;
    QString openFileName;
//    QTreeWidgetItem *rootNode=new QTreeWidgetItem();
    bool isAnalaysized = false;//如果没有进行一键解析，就不能进行可视化分析
    bool isSelectFile = false;//如果没有选择文件，就不能进行一键解析
    void GenerateDataGraph(const QStringList &statFilePathList);

    void DrawImage(std::vector<double> data);
};

#endif // FIRSTWIDGET_H
