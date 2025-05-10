QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD \
               $$PWD/UI_tools

DEPENDPATH += $$PWD \
              $$PWD/UI_tools


SOURCES += \
    Netw_elems/base/netlink.cpp \
    Netw_elems/base/netnode.cpp \
    Netw_elems/controller.cpp \
    Netw_elems/ctoslink.cpp \
    Netw_elems/host.cpp \
    Netw_elems/hslink.cpp \
    Netw_elems/sslink.cpp \
    Netw_elems/switch.cpp \
    UI_tools/controllerdialog.cpp \
    UI_tools/hostdialog.cpp \
    UI_tools/linkparamdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    UI_tools/networkview.cpp

HEADERS += \
    Netw_elems/base/devices.h \
    Netw_elems/base/netlink.h \
    Netw_elems/base/netnode.h \
    Netw_elems/controller.h \
    Netw_elems/ctoslink.h \
    Netw_elems/host.h \
    Netw_elems/hslink.h \
    Netw_elems/sslink.h \
    Netw_elems/switch.h \
    UI_tools/controllerdialog.h \
    UI_tools/hostdialog.h \
    UI_tools/linkparamdialog.h \
    mainwindow.h \
    UI_tools/networkview.h

FORMS += \
    UI_tools/controllerdialog.ui \
    UI_tools/hostdialog.ui \
    UI_tools/linkparamdialog.ui \
    mainwindow.ui


RESOURCES += imgs/img.qrc


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
