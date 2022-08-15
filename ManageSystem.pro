#-------------------------------------------------
#
# Project created by QtCreator 2021-04-23T09:12:30
#
#-------------------------------------------------

QT   += core gui sql xml axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ManageSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        admin/adduserinfodialog.cpp \
        admin/adminwidget.cpp \
        cmessagebox/cmessagebox.cpp \
        commonhelper/DBOper.cpp \
        commonhelper/ExportExcel.cpp \
        delegate/checkboxdelegate.cpp \
        loginwidget.cpp \
        main.cpp \
        mainwidget.cpp \
        mouseevent.cpp \
        service/basicservice.cpp \
        service/userservice.cpp \
        statusbar.cpp \
        titlebar.cpp \
        user/userwidget.cpp

HEADERS += \
        admin/adduserinfodialog.h \
        admin/adminwidget.h \
        cmessagebox/cmessagebox.h \
        commonhelper/DBOper.h \
        commonhelper/ExportExcel.h \
        commonhelper/commonhelper.h \
        commonhelper/connection.h \
        delegate/checkboxdelegate.h \
        loginwidget.h \
        mainwidget.h \
        mouseevent.h \
        service/accountinfo.h \
        service/basicservice.h \
        service/userservice.h \
        statusbar.h \
        titlebar.h \
        user/userwidget.h

FORMS += \
        admin/adminwidget.ui \
        cmessagebox/cmessagebox.ui \
        loginwidget.ui \
        mainwidget.ui \
        statusbar.ui \
        titlebar.ui \
        user/userwidget.ui

DESTDIR+= $${PWD}/Bin

RESOURCES += \
    cmessagebox/resource.qrc \
    image.qrc

DISTFILES +=
