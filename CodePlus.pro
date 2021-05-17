QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DBLogin.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    DBLogin.h \
    mainwindow.h

FORMS += \
    DBLogin.ui \
    mainwindow.ui

TRANSLATIONS += \
    CodePlus_zh_CN.ts

INCLUDEPATH += \
    ./includeLib \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    DataBases.ini

