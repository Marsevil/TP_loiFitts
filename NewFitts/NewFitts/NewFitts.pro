QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controllers/fittscontroller.cpp \
    Views/configview.cpp \
    Views/graphview.cpp \
    Views/testview.cpp \
    main.cpp \
    Views/mainwindow.cpp

HEADERS += \
    Controllers/fittscontroller.h \
    Views/configview.h \
    Views/graphview.h \
    Views/mainwindow.h \
    Views/testview.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
