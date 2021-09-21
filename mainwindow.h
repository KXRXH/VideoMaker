#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>

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

private slots:
    void browseBtnEvent();
    void okBtnEvent();

};
#endif // MAINWINDOW_H
