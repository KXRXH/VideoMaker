#include "mainwindow.h"
#include "darktheme.h"
#include <QtWidgets>
#include <QCoreApplication>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QFileInfo>
#include <iostream>
#include <fstream>

QStringList FILES_LIST;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    darktheme dt;
    //MainWindow setup
    this->setFixedSize(500, 300);

    //"BROWSE" BUTTON setup
    BROWSE_BUTTON = new QPushButton("Browse", this);
    BROWSE_BUTTON->move(10, 250);
    BROWSE_BUTTON->resize(235, 40);
    BROWSE_BUTTON->setToolTip("Browse video file");
    BROWSE_BUTTON->setStyleSheet(dt.QButtonSheet);
    connect(BROWSE_BUTTON, SIGNAL(clicked()), this, SLOT(browseBtnEvent()), Qt::UniqueConnection);

    //"OK" BUTTON setup
    OK_BUTTON = new QPushButton("Ok", this);
    OK_BUTTON->setToolTip("Create a video");
    OK_BUTTON->move(255, 250);
    OK_BUTTON->setStyleSheet(dt.QButtonSheet);
    OK_BUTTON->resize(235, 40);
    connect(OK_BUTTON, SIGNAL(clicked()), this, SLOT(okBtnEvent()), Qt::UniqueConnection);

    //QTableWidget with files list setup
    FILES_TABLE = new QTableWidget(this);
    FILES_TABLE->move(10, 10);
    FILES_TABLE->resize(480, 230);

    FILES_TABLE->setColumnCount(2);
    FILES_TABLE->horizontalHeader()->hide();
    FILES_TABLE->setEditTriggers(QTableWidget::NoEditTriggers);
    FILES_TABLE->setShowGrid(false);
}

void MainWindow::okBtnEvent()
{
    QString outFileName = QFileDialog::getSaveFileName(this,
                                            tr("Save file"), "/", tr("Video File (*.mp4)"));
    std::string cmd = QString("ffmpeg -safe 0 -f concat -i files.txt -c copy %1").arg(outFileName).toStdString();
    WinExec(cmd.c_str(), SW_HIDE);
    FILES_TABLE->setRowCount(0);
}


void MainWindow::browseBtnEvent()
{
    QStringList FILES = QFileDialog::getOpenFileNames(this,
                                            tr("Choose video files"), "/", tr("Video File (*.mp4)"));
    if (FILES.size())
    {
        QFileInfo fileListInfo("files.txt");
        bool test = fileListInfo.exists() && fileListInfo.isFile();
        std::ofstream outfile;
        if (test)
        {
            outfile.open("files.txt", std::ios_base::app);

        }
        else {
            outfile.open("files.txt");
        }
        for (auto& path : FILES)
        {


            FILES_TABLE->setRowCount(FILES_TABLE->rowCount() + 1);
            QFileInfo fi(path);
            QString FileName = fi.fileName();
            QString FileSize = QString("%1 Mb").arg(QString::number(fi.size() / pow(1024, 2)));
            FILES_TABLE->setItem(FILES_TABLE->rowCount() - 1, 0, new QTableWidgetItem(FileName));
            FILES_TABLE->setItem(FILES_TABLE->rowCount() - 1, 1, new QTableWidgetItem(FileSize));

            outfile << "file '" << path.toStdString() << "'\n";
        }
        outfile.close();
    }
}
MainWindow::~MainWindow(){}

