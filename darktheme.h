#ifndef DARKTHEME_H
#define DARKTHEME_H

#include <QMainWindow>
#include <QObject>
#include <QPalette>

class darktheme
{
public:
    // const QString QButtonSheet = "QPushButton {border: 1px solid white;border-style: outset;border-radius: 5px;text-align: center}"
    //                             "QPushButton::pressed{background-color: rgba(149, 165, 166, 1);border-style: inset;border: 1.2px solid black;}"
    //                             "QPushButton::hover::!pressed {background-color: rgb(46, 46, 46);}";
    const QString QToolTipSheet = "QToolTip { color: #ffffff; background-color: rgb(43, 43, 43); border: 1px solid white; }";
    QPalette getDarkTheme();
};

#endif // DARKTHEME_H
