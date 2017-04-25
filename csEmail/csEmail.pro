#-------------------------------------------------
#
# Project created by QtCreator 2017-04-12T20:18:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = csEmail
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    MyBase64.cpp \
    MyPop.cpp \
    MyQuotedPrintable.cpp \
    MySmtp.cpp \
    MySocket.cpp \
    NaviBar.cpp \
    MailList.cpp \
    BoxLists.cpp \
    WriteMailDlg.cpp \
    AboutDlg.cpp \
    Settings.cpp \
    QMainWin.cpp \
    SendingDlg.cpp \
    AutoLineEdit.cpp \
    OpenMailDlg.cpp

HEADERS  += \
    qt.h \
    structdef.h \
    MyBase64.h \
    MyPop.h \
    MyQuotedPrintable.h \
    MySmtp.h \
    MySocket.h \
    NaviBar.h \
    MailList.h \
    BoxLists.h \
    WriteMailDlg.h \
    AboutDlg.h \
    Settings.h \
    QMainWin.h \
    SendingDlg.h \
    AutoLineEdit.h \
    OpenMailDlg.h

RESOURCES += \
    img.qrc

DISTFILES +=
