#include "mainwindow.h"



std::vector<std::string> _filesVector;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //MainWindow setup
    this->setFixedSize(500, 300);

    //"BROWSE" BUTTON setup
    BROWSE_BUTTON = new QPushButton("Browse", this);
    BROWSE_BUTTON->move(10, 250);
    BROWSE_BUTTON->resize(235, 40);
    BROWSE_BUTTON->setToolTip("Browse video file");
    connect(BROWSE_BUTTON, SIGNAL(clicked()), this, SLOT(browseBtnEvent()), Qt::UniqueConnection);

    //"OK" BUTTON setup
    OK_BUTTON = new QPushButton("Ok", this);
    OK_BUTTON->setToolTip("Create a video");
    OK_BUTTON->move(255, 250);
    OK_BUTTON->resize(235, 40);
    connect(OK_BUTTON, SIGNAL(clicked()), this, SLOT(okBtnEvent()), Qt::UniqueConnection);

    //QTableWidget with files list setup
    FILES_TABLE = new QTableWidget(this);
    FILES_TABLE->move(10, 10);
    FILES_TABLE->resize(480, 230);
    FILES_TABLE->setColumnCount(3);
    FILES_TABLE->horizontalHeader()->hide();
    FILES_TABLE->setEditTriggers(QTableWidget::NoEditTriggers);
    FILES_TABLE->setShowGrid(false);
    QFont fnt = FILES_TABLE->font();
    fnt.setPointSize(10);
    FILES_TABLE->setFont(fnt);
    //Setting resize policy
    FILES_TABLE->horizontalHeader()->setStretchLastSection(true);
    FILES_TABLE->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}


void MainWindow::okBtnEvent()
{
    QString outFileName = QFileDialog::getSaveFileName(this,
                                            tr("Save file"), "/", tr("Video File (*.mp4)"));
    if (outFileName != "")
    {    
        // Creating one big video file from clips (clip's names are insede files.txt)
        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(_filesVector), std::end(_filesVector), rng); // random shuffle
        QFileInfo fileListInfo("files.txt");
        std::ofstream outfile;
        //Checking does file exists
        if (fileListInfo.exists() && fileListInfo.isFile())
        {
            outfile.open("files.txt", std::ios_base::app); // Adding to file

        }
        else {
            outfile.open("files.txt"); // Creating new file
        }
        for (auto& data : _filesVector)
        {
           outfile << data;
        }
        outfile.close();
        const std::string cmd = QString("ffmpeg -safe 0 -f concat -i files.txt -c copy \"%1\"").arg(outFileName).toStdString();
        system(cmd.c_str());
        // Clearing QTableWidget
        FILES_TABLE->setRowCount(0);
        std::ofstream ofs;
        ofs.open("files.txt", std::ofstream::trunc);
        ofs.close();
        _filesVector.clear();
    }
}

void MainWindow::browseBtnEvent()
{
    QStringList FILES = QFileDialog::getOpenFileNames(this,
                                            tr("Choose video files"), "/", tr("Video File (*.mp4)"));
    if (FILES.size())
    {
        for (auto& path : FILES)
        {
            // Filling table
            QFileInfo fi(path);
            QString FileName = fi.fileName();
            QString FileSize = QString("%1 Mb").arg(QString::number(fn.round_up(fi.size() / pow(1024, 2), 2)));
            FILES_TABLE->setRowCount(FILES_TABLE->rowCount() + 1);
            std::string surl = path.toStdString();
            const char *cstr = surl.c_str();
            char* url= getDur((char*)cstr);
            free(url);
            double fFileDurationSec = QString::fromLocal8Bit(url).toDouble();
            int FileDurationSec = (int) fFileDurationSec;
            std::string seconds = fn.to_format(FileDurationSec % 60);
            int minutes = FileDurationSec / 60;
            std::string hours = fn.to_format(minutes / 60);
            std::string minutesStr = fn.to_format(FileDurationSec / 60);
            QString FILE_DURATION = QString("%1:%2:%3").arg(QString::fromUtf8(hours), QString::fromUtf8(minutesStr), QString::fromUtf8(seconds));
            FILES_TABLE->setItem(FILES_TABLE->rowCount() - 1, 0, new QTableWidgetItem(FileName));
            FILES_TABLE->setItem(FILES_TABLE->rowCount() - 1, 1, new QTableWidgetItem(FileSize));
            FILES_TABLE->setItem(FILES_TABLE->rowCount() - 1, 2, new QTableWidgetItem(FILE_DURATION));
            
            // Writing paths to file
            std::string pathToFile= fn.ReplaceAll(path.toStdString(), std::string("'"), std::string("'\\''"));
            std::stringstream ss;
            ss << "file '" << pathToFile << "'\n";
            _filesVector.push_back(ss.str());
        }
    }
}
MainWindow::~MainWindow(){}

