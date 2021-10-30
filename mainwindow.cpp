#include "mainwindow.h"
#include "functions.h"
#include "fileduration.h"


struct Duration
{
    int sec;
    int min;
    int hour;
    //-------------------------------------------------------------------------------------------------------//
    // Initializing fucntions for formating nums to format of <00:00:00>
    std::string strsec() const { return to_format(sec); }
    std::string strmin() const { return to_format(min); }
    std::string strhour() const { return to_format(hour); }
};

std::vector<std::string> _filesVector; // Creating std::vector<std::string> for randomizing order of loaded videos by randomizing files names.

Duration GENERAL_DURATION = {0, 0, 0}; // Creating struct for getting sum of all video durations.

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //MainWindow setup
    this->setFixedSize(500, 320);
//-------------------------------------------------------------------------------------------------------//
    //"BROWSE" BUTTON setup.
    BROWSE_BUTTON = new QPushButton("Browse", this);
    BROWSE_BUTTON->move(10, 270);
    BROWSE_BUTTON->resize(235, 40);
    BROWSE_BUTTON->setToolTip("Browse video file");
    connect(BROWSE_BUTTON, SIGNAL(clicked()), this, SLOT(browseBtnEvent()), Qt::UniqueConnection);
//-------------------------------------------------------------------------------------------------------//
    //"OK" BUTTON setup.
    OK_BUTTON = new QPushButton("Ok", this);
    OK_BUTTON->setToolTip("Create a video");
    OK_BUTTON->move(255, 270);
    OK_BUTTON->resize(235, 40);
    connect(OK_BUTTON, SIGNAL(clicked()), this, SLOT(okBtnEvent()), Qt::UniqueConnection);
//-------------------------------------------------------------------------------------------------------//
    //QTableWidget with files list setup.
    FILES_TABLE = new QTableWidget(this);
    FILES_TABLE->move(10, 10);
    FILES_TABLE->resize(480, 230);
    FILES_TABLE->setColumnCount(3);
    FILES_TABLE->horizontalHeader()->hide();
    FILES_TABLE->setEditTriggers(QTableWidget::NoEditTriggers);
    FILES_TABLE->setShowGrid(false);
    // Changeing font size.
    QFont fnt = FILES_TABLE->font();
    fnt.setPointSize(10);
    FILES_TABLE->setFont(fnt);
    //Setting resize policy.
    FILES_TABLE->horizontalHeader()->setStretchLastSection(true);
    FILES_TABLE->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//-------------------------------------------------------------------------------------------------------//
    // "General Duration" QLabel setup.
    FILES_DURATIONS = new QLabel(this);
    FILES_DURATIONS->move(10, 230);
    FILES_DURATIONS->resize(200, 50);
    FILES_DURATIONS->setText("Out file duration: 00:00:00");
    // Changeing font size.
    fnt.setPointSize(12);
    FILES_DURATIONS->setFont(fnt);
}

//-------------------------------------------------------------------------------------------------------//

void MainWindow::okBtnEvent()
{
    QString outFileName = QFileDialog::getSaveFileName(this,
                                            tr("Save file"), "/", tr("Video File (*.mp4)"));
    if (!outFileName.isEmpty())
    {    
        auto rng = std::mt19937(std::time(nullptr)); // Creating generator.
        std::shuffle(std::begin(_filesVector), std::end(_filesVector), rng); // Randomizing order of videos.

        std::ofstream outfile;
        outfile.open("files.tmp");
        for (auto&& data : _filesVector) outfile << data;
        outfile.close();

        // Creating video by running FFPROBE from cmd.
        // Creating one big video file from clips (clip's names are insede files.txt)
        const std::string cmd = QString("ffmpeg -safe 0 -f concat -i files.tmp -c copy \"%1\"").arg(outFileName).toStdString();
        system(cmd.c_str());

        // Clearing QTableWidget
        QAbstractItemModel* const table_model = FILES_TABLE->model();
        table_model->removeRows(0, table_model->rowCount());

        // Removing .tmp file with files names.
        std::remove("files.tmp");
        GENERAL_DURATION = {0, 0, 0};

        // General duration zeroing
        FILES_DURATIONS->setText("Out file duration: 00:00:00");

        _filesVector.clear();
    }
}

//-------------------------------------------------------------------------------------------------------//

void MainWindow::browseBtnEvent()
{
    QStringList FILES = QFileDialog::getOpenFileNames(this,
                                            tr("Choose video files"), "/", tr("Video File (*.mp4)"));
    if (FILES.size())
    {
        for (auto&& path : FILES)
        {
            // Writing paths to file.
            std::string pathToFile= ReplaceAll(path.toStdString(), std::string("'"), std::string("'\\''"));
            std::stringstream ss;
            ss << "file '" << pathToFile << "'\n";
            _filesVector.push_back(ss.str());
            //-------------------------------------------------------------------------------------------------------//
            // Getting file size.
            QFileInfo fi(path);
            QString FileName = fi.fileName();
            QString FileSize = QString("%1 Mb").arg(QString::number(round_up(fi.size() / pow(1024, 2), 2)));            
            //-------------------------------------------------------------------------------------------------------//
            // Getting video file duration.
            int FileDurationSec;
            getVideoDuration((char*)path.toStdString().c_str(), FileDurationSec); // calling cgo lib [char* getDur(char* url)]
            Duration * FDURATION = new Duration {FileDurationSec % 60, FileDurationSec / 60, FileDurationSec / 360};
            GENERAL_DURATION.sec += FDURATION->sec;
            GENERAL_DURATION.min += FDURATION->min;
            GENERAL_DURATION.hour += FDURATION->hour;
            timeFormat(GENERAL_DURATION);
            QString FILE_DURATION = QString("%1:%2:%3").arg(QString::fromUtf8(FDURATION->strhour()),
                                                            QString::fromUtf8(FDURATION->strmin()),
                                                            QString::fromUtf8(FDURATION->strsec()));
            //-------------------------------------------------------------------------------------------------------//
            // Filling the table.
            FILES_TABLE->setRowCount(FILES_TABLE->rowCount() + 1);
            FILES_DURATIONS->setText(QString("Out file duration: %1:%2:%3").arg(QString::fromUtf8(GENERAL_DURATION.strhour()),
                                                                                QString::fromUtf8(GENERAL_DURATION.strmin()),
                                                                                QString::fromUtf8(GENERAL_DURATION.strsec())));
            FILES_TABLE->setItem(FILES_TABLE->rowCount() - 1, 0, new QTableWidgetItem(FileName));
            FILES_TABLE->setItem(FILES_TABLE->rowCount() - 1, 1, new QTableWidgetItem(FileSize));
            FILES_TABLE->setItem(FILES_TABLE->rowCount() - 1, 2, new QTableWidgetItem(FILE_DURATION));
            //-------------------------------------------------------------------------------------------------------//
            // Memory cleaning.
            delete FDURATION;
        }
    }
}
MainWindow::~MainWindow(){}

