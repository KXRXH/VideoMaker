#ifndef DARKTHEME_H
#define DARKTHEME_H

#include <QMainWindow>
#include <QObject>
#include <QPalette>

class darktheme
{
public:
    const QString QToolTipSheet = "QToolTip { color: #ffffff; background-color: rgb(43, 43, 43); border: 1px solid white; }";
    QPalette getDarkTheme();
};

#endif // DARKTHEME_H
