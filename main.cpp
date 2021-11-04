#include "mainwindow.h"

#include <QApplication>
#include <QFileInfo>
#include <QStyleFactory>
#include <darktheme.h>
#include <fstream>

int main(int argc, char *argv[]) {
  darktheme dt;
  QFileInfo fileListInfo("files.tmp");
  //-------------------------------------------------------------------------------------------------------//
  QApplication app(argc, argv);
  MainWindow window;
  //-------------------------------------------------------------------------------------------------------//
  // Dark theme applying.
  app.setStyle(QStyleFactory::create("Fusion"));
  app.setPalette(dt.getDarkTheme());
  app.setStyleSheet(dt.QToolTipSheet);
  //-------------------------------------------------------------------------------------------------------//
  // Checking does files.tmp exists if <true> delete it.
  if (fileListInfo.exists() && fileListInfo.isFile())
    std::remove("files.tmp");

  window.show();
  return app.exec();
}
