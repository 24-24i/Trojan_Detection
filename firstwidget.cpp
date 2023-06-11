#include "firstwidget.h"
#include "ui_firstwidget.h"
#include <QScreen>
#include <QPushButton>
#include <QStackedWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QSaveFile>
#include <QPixmap>
#include <QDir>
#include <QCheckBox>
#include <QFileInfo>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <io.h>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QAbstractAxis>
#include <highlighter.h>>

QT_USE_NAMESPACE

FirstWidget::FirstWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::FirstWidget) {
    ui->setupUi(this);

    // 页面效果调整
    setWindowIcon(QIcon(":/pic/logo.jpg"));
    setFixedSize(1200, 700);
    // 居中显示
    QScreen *desk = QGuiApplication::primaryScreen();
    int wd = desk->size().width();
    int ht = desk->size().height();
    move((wd - width()) / 2, (ht - height()) / 2);
    // 默认情况下显示0号页
    ui->stackedWidget->setCurrentIndex(0);
    // 布局控件参数调整
    ui->verticalSpacer->changeSize(4, 4);//弹簧长度

    /*stackwidget0*/
    // 可视化分析
    connect(ui->fpb1, &QPushButton::clicked, [=]() {
        if (isAnalaysized == true) {
            ui->stackedWidget->setCurrentIndex(1);
        } else {
            QMessageBox::warning(this, "解析错误", "尚未选择文件!");
        }
    });

    // 进度条相关操作
    analyzeTimer = new QTimer(this); //初始化定时器
    analyzeTimer->setInterval(30); //设置间隔
    // 进度条开始和一键解析按钮关联
    connect(ui->fpb3, &QPushButton::clicked, this, &FirstWidget::onfpb3begin);
    // 时间到后 调用超时函数，弹出提示框
    connect(analyzeTimer, &QTimer::timeout, this, &FirstWidget::onfpb3timeout);
    //清空数据和图像
    connect(ui->clearButton, &QPushButton::clicked, this, &FirstWidget::clear);

    // 文件选择并展示
    connect(ui->fpb2, &QPushButton::clicked, [=]() {
        //选择文件对话框
        QString path = QFileDialog::getOpenFileName(this, "打开文件");
        ui->fileedit->setText(path);
        //读取内容 放到text框里
        QFile file(path);
        file.open(QIODevice::ReadOnly);
        QByteArray array = file.readAll();
        ui->ftext->setText(array);
        ui->ftext->setReadOnly(true);

        // 关键词高亮显示
        if (!array.isEmpty()) {
            KeywordHighlighter *highlighter = new KeywordHighlighter(ui->ftext->document());
        }

    });

    /*stackwidget1*/
    // 返回
    connect(ui->spb0, &QPushButton::clicked, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    // 退出
    connect(ui->spb1, &QPushButton::clicked, [=]() {
        this->close();
    });
    connect(ui->quitButton, &QPushButton::clicked, [=]() {
        this->close();
    });
    // 保存图像
    connect(ui->spb2, &QPushButton::clicked, this, &FirstWidget::savefile);

    // 左侧下拉目录（treewidget+信号槽连接）
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->header()->hide();
    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    QTreeWidgetItem *rootNode = new QTreeWidgetItem(ui->treeWidget, QStringList() << "目录");
    rootNode->setFlags(rootNode->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsUserCheckable);
    QString folderPath = "./Outputs"; // 存储 stat 文件的文件夹路径
    QStringList statFilePathList; //存储 stat 文件的路径
    if (!folderPath.isEmpty()) {
        QDir dir(folderPath);
        dir.setFilter(QDir::Files);
        dir.setNameFilters(QStringList() << "*.stat");
        QStringList statFileList = dir.entryList();
        for (const QString &statFile: statFileList) {
            QString filePath = folderPath + "/" + statFile;
            statFilePathList.append(filePath);
        }
    }
    for (const QString &statFilePath: statFilePathList) {
        QTreeWidgetItem *item = new QTreeWidgetItem(rootNode, QStringList()
                << "    " + QFileInfo(statFilePath).fileName().split(".stat")[0]);
        item->setFlags(item->flags() | Qt::ItemIsEnabled);
    }
    for (int i = 0; i < rootNode->childCount(); i++) {
        QTreeWidgetItem *item = rootNode->child(i);
        QCheckBox *checkBox = new QCheckBox();
        checkBox->setChecked(false);
        checkBox->setStyleSheet("QCheckBox {}");
        ui->treeWidget->setItemWidget(item, 0, checkBox);
    }

    // 全选键
    connect(ui->selectAll, &QPushButton::clicked, [=]() {
        static bool isSelectAll = true;
        for (int i = 0; i < rootNode->childCount(); i++) {
            QTreeWidgetItem *item = rootNode->child(i);
            QCheckBox *checkBox = qobject_cast<QCheckBox *>(ui->treeWidget->itemWidget(item, 0));
            if (checkBox) {
                checkBox->setChecked(isSelectAll);
            }
        }
        isSelectAll = !isSelectAll;
        ui->selectAll->setText(isSelectAll ? "全选" : "全不选");
    });


    // 图像生成键
    connect(ui->getIMG, &QPushButton::clicked, [=]() {

        // 获取数据

        // 遍历节点，获取选中的节点
        QList<QTreeWidgetItem *> itemList;
        for (int i = 0; i < rootNode->childCount(); i++) {
            QTreeWidgetItem *item = rootNode->child(i);
            QCheckBox *checkBox = qobject_cast<QCheckBox *>(ui->treeWidget->itemWidget(item, 0));
            if (checkBox && checkBox->isChecked()) {
                itemList.append(item);
            }
        }
        // 如果没有选中任何节点，则提示用户选择节点
        if (itemList.isEmpty()) {
            QMessageBox::warning(this, "无法生成图像", "请至少选择一个节点");
            return;
        }
        // 提取数据
        std::vector<std::string> paths;
        for (auto &item: itemList) {
            QString path = folderPath + "/" + item->text(0).trimmed() + ".stat";
            paths.push_back(path.toStdString());
        }
        //将数据写入textEdit
        for (std::string path: paths) {
            QString path_temp = QString::fromStdString(path);
            QFile file(path_temp);
            file.open(QIODevice::ReadOnly);
            QByteArray array = file.readAll();
            ui->textEdit->setText("输出（各LUT的信息熵）：");
            ui->textEdit->append(array);
            ui->textEdit->setReadOnly(true);
        }

        std::vector<double> data;
        for (auto &file: paths) {
            std::ifstream in(file);
            if (in) { // 将数据添加进序列
                std::string line;
                std::getline(in, line); // 跳过第一行
                while (std::getline(in, line)) {
                    std::stringstream ss(line);
                    std::vector<std::string> tokens;
                    std::copy(std::istream_iterator<std::string>(ss), std::istream_iterator<std::string>(),
                              std::back_inserter(tokens));
                    // 读取非空行数据
                    if (!tokens.empty())
                        data.push_back(std::stod(tokens.back()));
                }
            }
        }

        // 绘制图像

        QChartView *chartView = new QChartView(this);
        QChart *chart = new QChart();
        QBarSeries *series = new QBarSeries(chart);

        // 生成直方图数据并添加数据至series
        QVector<double> vector_data(data.size());
        std::copy(data.begin(), data.end(), vector_data.begin());

        QVector<int> hist_data(20);
        int start = 0;
        int end = 1;
        double interval = (end - start) / 20.0;
        for (int i = 0; i < vector_data.size(); ++i) {
            int index = qFloor((vector_data[i] - start) / interval);
            if (index >= 0 && index < hist_data.size()) {
                hist_data[index]++;
            }
            if (index == 20) {
                hist_data[19]++;
            }
        }
        auto max = std::max_element(std::begin(hist_data), std::end(hist_data));
        int biggest = *max;

        QBarSet *set = new QBarSet("");
        for (int i = 0; i < 20; i++) {
            *set << hist_data[i];
        }

        series->append(set);
        series->setLabelsVisible(true);
        chart->legend()->setVisible(false);
        chart->addSeries(series);
        series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
        set->setLabelColor(Qt::black);
        series->setBarWidth(0.75);

        // 创建横纵轴对象，设置标签
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        QValueAxis *axisY = new QValueAxis();

        QStringList categories;
        for (int i = 0; i < hist_data.size(); i++) {
            // 显示0.00-0.05, 0.05-0.10, ..., 0.95-1.00标签
            QString label = QString("%1-%2").arg(i * 0.05, 0, 'f', 2).arg((i + 1) * 0.05, 0, 'f', 2);
            categories << label;
        }

        // 标签格式设置
        axisX->append(categories);
        chart->createDefaultAxes();
        chart->setAxisX(axisX, series);
        chart->setAxisY(axisY, series);
        chart->axes(Qt::Vertical).first()->setRange(0, (round(biggest / 100.0) + 1) * 100);
        axisX->setLabelsFont(QFont("Arial", 5));
        axisY->setLabelsFont(QFont("Arial", 6));
        axisY->setLabelFormat("%d");

        // 将序列与坐标轴关联起来
        series->attachAxis(axisX);
        series->attachAxis(axisY);

        chartView->setChart(chart);
        chartView->resize(950, 500);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->show();
        chartView->repaint();

        // 截图并将其转换为QPixmap
        QImage screenshot = chartView->grab().toImage();
        QPixmap pixmap = QPixmap::fromImage(screenshot);
        chartView->close();

        // 将QPixmap显示为QLabel
        ui->label->setPixmap(pixmap);

        // QMessageBox::information(this, "生成数据图", "生成成功");
    });

}

FirstWidget::~FirstWidget() {
    delete ui;
}


void FirstWidget::onfpb3begin()//开始函数
{
    analyzeTimer->start();
}

void FirstWidget::onfpb3timeout()//超时函数
{
    int currentvalue = ui->progressBar->value();
    if (currentvalue >= ui->progressBar->maximum()) {
        analyzeTimer->stop();
        this->isAnalaysized = true;
        QMessageBox::information(this, "模块化解析", "解析完成");
    } else {
        ui->progressBar->setValue(ui->progressBar->value() + 4);
    }
}

void FirstWidget::savefile() {
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Image"), "Trojan Detection",
                                                    tr("Images (*.png *.bmp *.jpg)")); //选择路径
    if (!filename.isEmpty()) {
        // 从标签中获取Pixmap，并将其保存到指定文件
        QPixmap pixmap = ui->label->pixmap();
        pixmap.save(filename);
        QMessageBox::information(this, "保存图像", "保存成功!");
    }
}


void FirstWidget::clear() {
    ui->textEdit->clear();
    ui->textEdit->setText("输出（各LUT的信息熵）：");
    ui->label->clear();
}

void FirstWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap pixMap;
}
