QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    additemdialog.cpp \
    addmemberdialog.cpp \
    addpurchasedialog.cpp \
    database_manager.cpp \
    date.cpp \
    deleteitemdialog.cpp \
    deletememberdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    member.cpp \
    miscellaneous_functions.cpp \
    updateitemdialog.cpp

HEADERS += \
    additemdialog.h \
    addmemberdialog.h \
    addpurchasedialog.h \
    database_manager.h \
    date.h \
    deleteitemdialog.h \
    deletememberdialog.h \
    mainwindow.h \
    member.h \
    miscellaneous_functions.h \
    updateitemdialog.h

FORMS += \
    additemdialog.ui \
    addmemberdialog.ui \
    addpurchasedialog.ui \
    deleteitemdialog.ui \
    deletememberdialog.ui \
    mainwindow.ui \
    updateitemdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
