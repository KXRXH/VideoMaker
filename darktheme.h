#ifndef DARKTHEME_H
#define DARKTHEME_H

#include <QMainWindow>
#include <QObject>
#include <QPalette>

class darktheme
{
public:
    const QString QButtonSheet = "QPushButton {border: 1px solid white;border-style: outset;border-radius: 5px;text-align: center}QPushButton::pressed {background-color: rgba(149, 165, 166, 1);border-style: inset;border: 1.2px solid black;}QPushButton::hover::!pressed {background-color: rgba(108, 122, 137, 1);}";
    const QString QToolTipSheet = "QToolTip { color: #ffffff; background-color: rgb(53, 53, 53); border: 1px solid white; }";
    QPalette getDarkTheme();
};

#endif // DARKTHEME_H
