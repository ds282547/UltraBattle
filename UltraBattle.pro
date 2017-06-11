#-------------------------------------------------
#
# Project created by QtCreator 2017-05-11T19:56:26
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UltraBattle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    minion.cpp \
    miniondata.cpp \
    typedata.cpp \
    pixmaps.cpp \
    actionframes.cpp \
    gpscene.cpp \
    msg.cpp \
    minionwarrior.cpp \
    hpbar.cpp \
    card.cpp \
    gpview.cpp \
    manabar.cpp \
    tower.cpp \
    minionspear.cpp \
    minionpriest.cpp \
    minionarchmage.cpp \
    minionbowman.cpp \
    minionknight.cpp \
    minionsiegeram.cpp \
    minionking.cpp \
    attackableobject.cpp \
    cannonball.cpp \
    drawcard.cpp \
    carditem.cpp \
    gamedata.cpp \
    carddeckitem.cpp

HEADERS  += mainwindow.h \
    game.h \
    minion.h \
    gamedata.h \
    miniondata.h \
    typedata.h \
    pixmaps.h \
    actionframes.h \
    gameconstdata.h \
    gpscene.h \
    msg.h \
    minionwarrior.h \
    hpbar.h \
    card.h \
    gpview.h \
    manabar.h \
    tower.h \
    minionspear.h \
    minionpriest.h \
    minionarchmage.h \
    minionbowman.h \
    minionknight.h \
    minionsiegeram.h \
    minionking.h \
    attackableobject.h \
    cannonball.h \
    drawcard.h \
    carditem.h \
    carddeckitem.h

FORMS    += mainwindow.ui \
    game.ui



RESOURCES += \
    pic.qrc
