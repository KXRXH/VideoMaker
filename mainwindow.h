#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QtWidgets>
#include <QCoreApplication>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QFileInfo>
#include <string>
#include <fstream>
#include <QFont>
#include <sstream>
#include <algorithm>
#include <vector>
#include <random>
#include <cmath>
#include <ctime>
#include <QLabel>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QPushButton *BROWSE_BUTTON;
    QPushButton *OK_BUTTON;
    QTableWidget *FILES_TABLE;
    QLabel *FILES_DURATIONS;
    QPushButton *RESET_BUTTON;

private slots:
    void browseBtnEvent();
    void okBtnEvent();
    void resetBtnEvent();

};
#endif // MAINWINDOW_H
