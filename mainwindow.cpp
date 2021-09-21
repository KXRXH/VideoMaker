#include "mainwindow.h"
#include "darktheme.h"
#include <sys/stat.h>
#include <QtWidgets>
#include <QCoreApplication>
#include <QFileDialog>
#include <QDebug>
#include <QThreadPool>
#include <QTableWidgetItem>
#include <QFileInfo>
#include <fstream>
#include <winbase.h>



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
    BROWSE_BUTTON->resize(215, 40);
    BROWSE_BUTTON->setToolTip("Browse video file");
    BROWSE_BUTTON->setStyleSheet(dt.QButtonSheet);
    connect(BROWSE_BUTTON, SIGNAL(clicked()), this, SLOT(browseBtnEvent()), Qt::UniqueConnection);

    //"MODE" BUTTON setup
    MODE_BUTTON = new QPushButton("D", this);
    MODE_BUTTON->setToolTip("Now <direct> mode is used!");
    MODE_BUTTON->move(230, 250);
    MODE_BUTTON->setStyleSheet(dt.QButtonSheet);
    MODE_BUTTON->resize(40, 40);

    //"OK" BUTTON setup
    OK_BUTTON = new QPushButton("Ok", this);
    OK_BUTTON->setToolTip("Create a video");
    OK_BUTTON->move(275, 250);
    OK_BUTTON->setStyleSheet(dt.QButtonSheet);
    OK_BUTTON->resize(215, 40);
    connect(OK_BUTTON, SIGNAL(clicked()), this, SLOT(okBtnEvent()), Qt::UniqueConnection);

    //QTableWidget with files list setup
    FILES_TABLE = new QTableWidget(this);
    FILES_TABLE->move(10, 10);
    FILES_TABLE->resize(480, 230);

    //FILES_TABLE->setStyleSheet("::section{Background-color: rgba(46, 49, 49, 1)}");
    FILES_TABLE->setColumnCount(3);
    FILES_TABLE->horizontalHeader()->hide();
    FILES_TABLE->setEditTriggers(QTableWidget::NoEditTriggers);
    FILES_TABLE->setShowGrid(false);
}

void okBtnAction()
{}

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
            std::string cmd = QString("ffprobe -v error -show_entries format=duration -of default=noprint_wrappers=1:nokey=1 %1 > times.txt").arg(path).toStdString();
            WinExec(cmd.c_str(), SW_HIDE);
            FILES_TABLE->setItem(FILES_TABLE->rowCount() - 1, 0, new QTableWidgetItem(FileName));
            FILES_TABLE->setItem(FILES_TABLE->rowCount() - 1, 1, new QTableWidgetItem(FileSize));
            //FILES_TABLE->setItem(FILES_TABLE->rowCount() - 1, 2, new QTableWidgetItem(dur));
            outfile << "file '" << path.toStdString() << "'\n";
        }
        outfile.close();
    }
}
MainWindow::~MainWindow(){}

