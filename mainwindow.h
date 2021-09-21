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
    int MODE_TYPE = 0;
    int ROWS = 0;
private:
    QPushButton *MODE_BUTTON;
    QPushButton *BROWSE_BUTTON;
    QPushButton *OK_BUTTON;
    QTableWidget *FILES_TABLE;
    QStringList *FILES;
    QString *FILENAME;

private slots:
    void browseBtnEvent();
    void okBtnEvent();

};
#endif // MAINWINDOW_H
