QT += core gui\
      network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += \
    c++11 \
    pkgconfig \ # link_pkg for qterm
QTermWidget = qtermwidget5
PKGCONFIG += $${QTermWidget} # for qterm

LIBS += -lqtermwidget5

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD \
               $$PWD/UI_tools

DEPENDPATH += $$PWD \
              $$PWD/UI_tools


SOURCES += \
    File_tools/geneticcontrollergenerator.cpp \
    File_tools/jsonprocessor.cpp \
    File_tools/metricexporter.cpp \
    File_tools/mininetbuilder.cpp \
    Netw_elems/base/netlink.cpp \
    Netw_elems/base/netnode.cpp \
    Netw_elems/controller.cpp \
    Netw_elems/ctoslink.cpp \
    Netw_elems/host.cpp \
    Netw_elems/hslink.cpp \
    Netw_elems/sslink.cpp \
    Netw_elems/switch.cpp \
    UI_tools/controllerdialog.cpp \
    UI_tools/geneticcontrollerdialog.cpp \
    UI_tools/hostdialog.cpp \
    UI_tools/linkparamdialog.cpp \
    UI_tools/ryudialog.cpp \
    main.cpp \
    mainwindow.cpp \
    UI_tools/networkview.cpp \
    tcp/listener.cpp \
    tcp/pathgetter.cpp \
    tcp/tcpserver.cpp

HEADERS += \
    File_tools/geneticcontrollergenerator.h \
    File_tools/jsonprocessor.h \
    File_tools/metricexporter.h \
    File_tools/mininetbuilder.h \
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
    UI_tools/geneticcontrollerdialog.h \
    UI_tools/hostdialog.h \
    UI_tools/linkparamdialog.h \
    UI_tools/ryudialog.h \
    mainwindow.h \
    UI_tools/networkview.h \
    tcp/listener.h \
    tcp/pathgetter.h \
    tcp/tcpserver.h

FORMS += \
    UI_tools/controllerdialog.ui \
    UI_tools/geneticcontrollerdialog.ui \
    UI_tools/hostdialog.ui \
    UI_tools/linkparamdialog.ui \
    UI_tools/ryudialog.ui \
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
