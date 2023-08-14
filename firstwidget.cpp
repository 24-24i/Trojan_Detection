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
//#include <io.h>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QAbstractAxis>
#include <highlighter.h>
#include <QProcess>

QT_USE_NAMESPACE

FirstWidget::FirstWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::FirstWidget) {
    ui->setupUi(this);

    // 页面效果调整
    setWindowIcon(QIcon(":/pic/logo.png"));
    setFixedSize(1700, 1000);
    // 居中显示
    QScreen *desk = QGuiApplication::primaryScreen();
    int wd = desk->size().width();
    int ht = desk->size().height();
    move((wd - width()) / 2, (ht - height()) / 2);
    // 默认情况下显示0号页
    ui->stackedWidget->setCurrentIndex(0);
    // 布局控件参数调整
//    ui->verticalSpacer->changeSize(4, 4); // 弹簧长度
    ui->textEdit->setText("输出（各LUT的信息熵）：");
    ui->processText->append("cmd:");
    ui->ftext->append("file:");

    // 左侧下拉目录（treewidget+信号槽连接）
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->header()->hide();
    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->treeWidget->setIndentation(10);
    QTreeWidgetItem *rootNode = new QTreeWidgetItem(ui->treeWidget, QStringList() << "目录");
    rootNode->setExpanded(true);
    rootNode->setFlags(rootNode->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsUserCheckable);

    // 文件选择并展示
    connect(ui->fpb2, &QPushButton::clicked, this, [=]() {
        // 选择文件对话框
        QString path = QFileDialog::getOpenFileName(this, "打开文件");
        ui->fileedit->setText(path);
        // 读取内容 放到text框里
        QFile file(path);
        file.open(QIODevice::ReadOnly);
        QByteArray array = file.readAll();
        ui->ftext->append(array);
        ui->ftext->setReadOnly(true);

        //给openFileName赋值
        QFileInfo fileInfo(path); //创建一个QFileInfo对象
        openFileName = fileInfo.fileName().split('.')[0]; //调用fileName()方法获取文件名
        qDebug()<<("openFileName:")<<openFileName;

        // 设置选择文件为true,这样便可以进行一键解析
        isSelectFile = true;
        // 关键词高亮显示
        if (!array.isEmpty()) {
            new KeywordHighlighter(ui->ftext->document());
        }

    });


    // 进度条相关操作,一键解析
    analyzeTimer = new QTimer(this); // 初始化定时器
    analyzeTimer->setInterval(30); // 设置间隔

    // 进度条开始和一键解析按钮关联
    // connect(ui->fpb3, &QPushButton::clicked, this, &FirstWidget::onfpb3begin);
    connect(ui->fpb3, &QPushButton::clicked, this, [=]() {
        if (isSelectFile==true)
        {
            onfpb3begin();
        }
        else
        {
            QMessageBox::warning(this, "错误", "尚未选择文件");
        }
        });

    // 时间到后 调用超时函数，弹出提示框
    connect(analyzeTimer, &QTimer::timeout, this, &FirstWidget::onfpb3timeout);
    // 清空数据和图像
    connect(ui->clearButton, &QPushButton::clicked, this, &FirstWidget::clear);



    /*stackwidget0*/
    // 可视化分析
    connect(ui->fpb1, &QPushButton::clicked, this, [=]() {
        if (isAnalaysized == true) {
            ui->stackedWidget->setCurrentIndex(1);
//            // 左侧下拉目录（treewidget+信号槽连接）
//            ui->treeWidget->setColumnCount(1);
//            ui->treeWidget->header()->hide();
//            ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
//            ui->treeWidget->setIndentation(10);
//            rootNode = new QTreeWidgetItem(ui->treeWidget, QStringList() << "目录");
//            rootNode->setExpanded(true);
//            rootNode->setFlags(rootNode->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsUserCheckable);
//            folderPath = QString("./Outputs"); // 存储 stat 文件的文件夹路径
            QStringList statFilePathList; // 存储 stat 文件的路径
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
                                                                          << QFileInfo(statFilePath).fileName().split(".stat")[0]);
                item->setFlags(item->flags() | Qt::ItemIsEnabled);
                item->setTextAlignment(0, Qt::AlignLeft);
                item->setCheckState(0, Qt::Unchecked);
            }

        } else {
            QMessageBox::warning(this, "解析错误", "尚未选择文件进行解析!");
        }
    });





    /*stackwidget1*/
    // 重新选择模块
//    ui->spb0->setText("重新选择模块");
    connect(ui->spb0, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
        ui->fileedit->clear();
        ui->ftext->clear();
        ui->processText->clear();
        ui->processText->append("cmd:");
        ui->ftext->append("file:");
//        ui->progressBar->reset();
        ui->progressBar->setValue(0);
        isAnalaysized = false;
        isSelectFile = false;
        clear();

        // 假设 parent 是一个 QTreeWidgetItem 对象
        QList<QTreeWidgetItem*> children = rootNode->takeChildren(); // 获取所有子节点的列表
        foreach (QTreeWidgetItem* child, children) {
            delete child; // 释放每个子节点的内存
        }

    });
    // 退出
    connect(ui->spb1, &QPushButton::clicked, this, [=]() {
        this->close();
    });
    connect(ui->quitButton, &QPushButton::clicked, this, [=]() {
        this->close();
    });
    // 保存图像
    connect(ui->spb2, &QPushButton::clicked, this, &FirstWidget::savefile);


    // 全选键
    connect(ui->selectAll, &QPushButton::clicked, this, [=]() {
        static bool isSelectAll = true;
        for (int i = 0; i < rootNode->childCount(); i++) {
            QTreeWidgetItem *item = rootNode->child(i);
            item->setCheckState(0, isSelectAll ? Qt::Checked : Qt::Unchecked);
        }
        isSelectAll = !isSelectAll;
        ui->selectAll->setText(isSelectAll ? "全选" : "全不选");
    });

    // 图像生成键
    connect(ui->getIMG, &QPushButton::clicked, this, [=]() {

        // 遍历节点，获取选中的节点
        QList<QTreeWidgetItem *> itemList;
        for (int i = 0; i < rootNode->childCount(); i++) {
            QTreeWidgetItem *item = rootNode->child(i);
            if (item->checkState(0) == Qt::Checked) {
                itemList.append(item);
            }
        }
        // 如果没有选中任何节点，则提示用户选择节点
        if (itemList.isEmpty()) {
            QMessageBox::warning(this, "无法生成图像", "请至少选择一个节点");
            return;
        }
        // 获取文件路径列表
        std::vector<std::string> paths;
        for (auto &item: itemList) {
            QString path = folderPath + "/" + item->text(0).trimmed() + ".stat";
            paths.push_back(path.toStdString());
        }
        // 将数据写入textEdit
        for (std::string path: paths) {

            std::string base_filename = path.substr(path.find_last_of("/\\") + 1);
            std::string::size_type p(base_filename.find_last_of('.'));
            std::string fileName = base_filename.substr(0, p);

            ui->textEdit->append(QString::fromStdString(fileName + ":"));
            QString path_temp = QString::fromStdString(path);
            QFile file(path_temp);
            file.open(QIODevice::ReadOnly);
            QByteArray array = file.readAll();
            ui->textEdit->append(array);
            // ui->textEdit->setReadOnly(true);
        }

        QStackedBarSeries *series = new QStackedBarSeries();

        QList<QVector<double>> data_list;
        if (!data_list.isEmpty()) {
            data_list.clear();
        }

        double min = 1;

        for (auto &file: paths) {

            std::string base_filename = file.substr(file.find_last_of("/\\") + 1); // 获取文件名和扩展名
            std::string::size_type p(base_filename.find_last_of('.')); // 获取最后一个点的位置
            std::string fileName = base_filename.substr(0, p); // 获取文件名

            auto *set = new QBarSet(QString::fromStdString(fileName)); // 初始化BarSet
            std::vector<double> data; // 存放模块中的原始数据

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
                    if (!tokens.empty()) {
                        double value = std::stod(tokens.back());
                        data.push_back(value);
                        // 更新全局最小元素
                        if (value < min) {
                            min = value;
                        }
                    }
                }
                QList<double> qList(data.begin(), data.end());
                data_list.append(qList); // 将数据向量添加到data_list中
            }
            series->append(set);
        }

        double x = qMin(qBound(0, qFloor(min / 0.05), 19) * 0.05, 1.0); // 计算区间的开始值

        for (int k = 0; k < series->count(); k++) {
            QBarSet *set = series->barSets().at(k); // 获取第k个BarSet对象
            QVector<double> vector_data = data_list[k];
            QVector<int> hist_data(20); // 存储数据分布情况

            for (int i = 0; i < vector_data.size(); ++i) {
                // 计算元素所属的区间的索引，添加对应频数
                int index = qFloor((vector_data[i] - x) / ((1 - x) / 20));
                if (index >= 0 && index < hist_data.size()) {
                    hist_data[index]++;
                }
                if (index == 20) {
                    hist_data[19]++; // 处理边界情况
                }
            }
            for (int i = 0; i < 20; i++) {
                *set << hist_data[i]; // 将频数添加到BarSet对象中
            }
        }

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        QMargins q;
        q.setBottom(1);
        chart->setMargins(q);

        series->setLabelsVisible(false);
        // series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
        series->setBarWidth(0.85);

        // 横纵轴标签
        QStringList categories;
        for (int i = 0; i < 20; i++) {
            QString label = QString("%1-").arg(i * (1 - x) / 20 + x, 0, 'f', 4);
            label.append("<br>");
            label.append(QString("%1").arg((i + 1) * (1 - x) / 20 + x, 0, 'f', 4));
            categories << label;
        }

        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        axisX->setLabelsFont(QFont("Arial", 7));
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);
        QValueAxis *axisY = new QValueAxis();
        axisY->setLabelsFont(QFont("Arial", 8));
        axisY->setLabelFormat("%d");
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        // 显示直方图
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setWindowFlags(Qt::WindowStaysOnBottomHint);
        chartView->setChart(chart);
        chartView->resize(1200,675);
        //chartView->resize(1920, 1080);
        chartView->show();
        chartView->repaint();

        // 截图并将其转换为QPixmap
        QImage screenshot = chartView->grab().toImage();
        QPixmap pixmap = QPixmap::fromImage(screenshot);
        chartView->close();

        // 将QPixmap显示为QLabel
        ui->label->setPixmap(pixmap);
    });

}

FirstWidget::~FirstWidget() {
    delete ui;
}

void FirstWidget::onfpb3begin() // 开始函数
{

    // Create a QProcess instance
    QProcess process;

    // Navigate to the desired directory where your commands should be executed
    QString workingDirectory = ".";
    process.setWorkingDirectory(workingDirectory);

    QDir dir("Outputs");
    if (dir.exists()) {
        dir.removeRecursively();
    }

    // Execute "./stat_xilinx" command

    process.start("./stat_xilinx");

    ui->processText->append("./stat_xilinx\n");
    qDebug("./stat_xilinx\n");

//    // 发送 sub_modules ./src/syn.v 到终端
//    process.write("sub_modules ./Sources/syn.v\n");
//    process.waitForBytesWritten();
//    qDebug("sub_modules ./Sources/syn.v");
//    // 发送 source ./Scripts/example1.sc 到终端
//    process.write("source ./Scripts/syn.sc\n");
//    process.waitForBytesWritten();
//    qDebug("source ./Scripts/syn.sc");

    // 发送 sub_modules ./src/syn.v 到终端
    QString cmd1=QString("sub_modules ./Sources/%1.v\n").arg(openFileName);
    process.write(cmd1.toUtf8().data());
    process.waitForBytesWritten();

    ui->processText->append(cmd1);
    qDebug(QString("sub_modules ./Sources/%1.v").arg(openFileName).toUtf8().data());
    // 发送 source ./Scripts/syn.sc 到终端
    QString cmd2=QString("source ./Scripts/%1.sc\n").arg(openFileName);
    process.write(cmd2.toUtf8().data());
    process.waitForBytesWritten();
    ui->processText->append(cmd2);
    qDebug(QString("source ./Scripts/%1.sc").arg(openFileName).toUtf8().data());

    // 发送 exit 到终端
    process.write("exit\n");
    process.waitForBytesWritten();
    ui->processText->append("exit");
    qDebug("exit");
    process.waitForFinished(-1); // Wait for the process to finish

    folderPath = QString("./Outputs"); // 存储 stat 文件的文件夹路径


    analyzeTimer->start();
}

void FirstWidget::onfpb3timeout() // 超时函数
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
    QString filename = QFileDialog::getSaveFileName(this, tr("保存图像至"), "Trojan Detection",
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
