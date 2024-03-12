#-------------------------------------------------
#
# Project created by QtCreator 2019-12-09T19:51:50
#
#-------------------------------------------------

QT       += testlib
QT       += gui widgets
QT       -= gui

TARGET = tst_objectmanagertest
CONFIG   += console
CONFIG   -= app_bundle

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


INCLUDEPATH += \
            ../../Game/ \
            ../../Game/core \
            ../../Game/graphics \
            ../../Course/CourseLib/ \

DEPENDPATH  += \
            ../../Game/ \
            ../../Game/core \
            ../../Course/CourseLib/ \

SOURCES += \
            tst_objectmanagertest.cpp\
#             ../../Game/core/objectmanager.cpp\
#             ../../Game/gameeventhandler.cpp\
#             ../../Course/CourseLib/core/playerbase.cpp\
#             ../../Course/CourseLib/core/coordinate.cpp\
#             ../../Course/CourseLib/core/gameobject.cpp\
#             ../../Course/CourseLib/buildings/buildingbase.cpp\
#             ../../Course/CourseLib/core/placeablegameobject.cpp\
#             ../../Course/CourseLib/tiles/tilebase.cpp\
#             ../../Course/CourseLib/workers/workerbase.cpp\
#             ../../Course/CourseLib/core/basicresources.cpp\
#             ../../Game/graphics/mapwindow.cc\
#             ../../Game/gamestate.cpp\
#             ../../Game/player.cpp\
#             ../../Game/graphics/gameview.cpp\
#             ../../Game/workers/farmer.cpp\
#             ../../Game/workers/miner.cpp\
#             ../../Game/workers/fisher.cpp\
#             ../../Game/workers/stonemason.cpp\
#             ../../Game/workers/lumberjack.cpp\

HHEADERS += \
#            ../../Game/core/objectmanager.hh\
#            ../../Course/CourseLib/interfaces/iobjectmanager.h\
#            ../../Course/CourseLib/core/playerbase.h\
#            ../../Course/CourseLib/core/coordinate.h\
#            ../../Course/CourseLib/core/gameobject.h\
#            ../../Course/CourseLib/buildings/buildingbase.h\
#            ../../Course/CourseLib/core/placeablegameobject.h\
#            ../../Course/CourseLib/tiles/tilebase.h\
#            ../../Course/CourseLib/workers/workerbase.h\
#            ../../Course/CourseLib/core/resourcemaps.h\
#            ../../Course/CourseLib/core/basicresources.h\
#            ../../Game/gameeventhandler.h\
#            ../../Game/graphics/mapwindow.hh\
#            ../../Game/gamestate.h\
#            ../../Game/player.h\
#            ../../Game/graphics/gameview.h\
#            ../../Game/workers/farmer.hh\
#            ../../Game/workers/miner.hh\
#            ../../Game/workers/fisher.h\
#            ../../Game/workers/stonemason.hh\
#            ../../Game/workers/lumberjack.hh\

