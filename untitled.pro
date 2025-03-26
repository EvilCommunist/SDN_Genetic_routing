QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD \
               $$PWD/UI_tools

DEPENDPATH += $$PWD \
              $$PWD/UI_tools


SOURCES += \
    UI_tools/linkparamdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    UI_tools/networkview.cpp

HEADERS += \
    UI_tools/linkparamdialog.h \
    mainwindow.h \
    UI_tools/networkview.h

FORMS += \
    UI_tools/linkparamdialog.ui \
    mainwindow.ui

win32 {
    CONFIG += console
    DEFINES += WIN32
} else:unix {
    DEFINES += UNIX
}

release {
    DEFINES += QT_NO_DEBUG_OUTPUT
    QMAKE_CXXFLAGS += -O2
}

debug {
    DEFINES += DEBUG
    QMAKE_CXXFLAGS += -g
}

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
