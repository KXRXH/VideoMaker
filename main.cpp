#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>
#include <darktheme.h>
#include <fstream>
#include <QFileInfo>
#include <QDebug>


int main(int argc, char *argv[])
{
    darktheme dt;
    QFileInfo fileListInfo("files.txt");
    
    QApplication app(argc, argv);
    MainWindow w;
    // Dark theme applying 
    app.setStyle(QStyleFactory::create("Fusion"));
    app.setPalette(dt.getDarkTheme());
    app.setStyleSheet(dt.QToolTipSheet);

    // Checking does files.txt exists and clearing it.
    if (fileListInfo.exists() && fileListInfo.isFile())
    {
        std::ofstream ofs;
        ofs.open("files.txt", std::ofstream::trunc);
        ofs.close();
    }
    w.show();
    return app.exec();
}
