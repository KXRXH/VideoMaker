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
#include <cmath>
#include "functions.h"
#include "darktheme.h"
#include "mylib.h"




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
    functions fn;
    darktheme dt;

private slots:
    void browseBtnEvent();
    void okBtnEvent();

};
#endif // MAINWINDOW_H
