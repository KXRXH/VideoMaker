#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>
#include <darktheme.h>
#include <fstream>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    darktheme dt;
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("Fusion"));
    app.setPalette(dt.getDarkTheme());
    app.setStyleSheet(dt.QToolTipSheet);
    MainWindow w;
    QFileInfo fileListInfo("files.txt");
    bool test = fileListInfo.exists() && fileListInfo.isFile();
    if (test)
    {
        std::ofstream ofs;
        ofs.open("files.txt", std::ofstream::trunc);
        ofs.close();
    }
    w.show();
    return app.exec();
}
