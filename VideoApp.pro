QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    darktheme.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    darktheme.h \
    fileduration.h \
    functions.h \
    mainwindow.h \    

FOLDER_PATH = ...                        # Example: D:/Programs/C++/VideoApp
INCLUDEPATH += $${FOLDER_PATH}/lib/libav/include
LIBS += -L$${FOLDER_PATH}/lib/libav/lib
LIBS += -lavcodec -lavfilter -lavformat -lavutil -lswscale


RC_FILE = $${FOLDER_PATH}\src\myapp.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
