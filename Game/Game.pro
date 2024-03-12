TEMPLATE = app
TARGET = TheGame

QT += core gui widgets

CONFIG += c++14

SOURCES += \
    buildings/employmentoffice.cpp \
    buildings/fishinghut.cpp \
    buildings/lumbermill.cpp \
    buildings/mine.cpp \
    buildings/quarry.cpp \
    core/objectmanager.cpp \
    game.cpp \
    gameeventhandler.cpp \
    gamestate.cpp \
    gameview.cpp \
    graphics/dialoggameend.cpp \
    graphics/dialoggamestart.cpp \
    graphics/gamescene.cpp \
    graphics/mapunititem.cpp \
    graphics/mapworkeritem.cpp \
    graphics/objectbutton.cpp \
    tiles/desert.cpp \
    tiles/hill.cpp \
    graphics/mapitem.cpp \
    graphics/mapwindow.cc \
    main.cpp \
    player.cpp \
    tiles/swamp.cpp \
    tiles/water.cpp \
    workers/farmer.cpp \
    workers/fisher.cpp \
    workers/lumberjack.cpp \
    workers/miner.cpp \
    workers/stonemason.cpp \
    workers/trainedworker.cpp


HEADERS += \
    buildings/employmentoffice.h \
    buildings/fishinghut.hh \
    buildings/lumbermill.hh \
    buildings/mine.hh \
    buildings/quarry.hh \
    core/gameresourcemaps.hh \
    core/objectmanager.hh \
    game.h \
    gameeventhandler.h \
    gamestate.h \
    gameview.h \
    graphics/dialoggameend.h \
    graphics/dialoggamestart.h \
    graphics/gamescene.h \
    graphics/mapunititem.h \
    graphics/mapworkeritem.h \
    graphics/objectbutton.h \
    tiles/desert.h \
    tiles/hill.hh \
    graphics/mapitem.h \
    graphics/mapwindow.hh \
    player.h \
    tiles/swamp.h \
    tiles/water.hh \
    workers/farmer.hh \
    workers/fisher.h \
    workers/lumberjack.hh \
    workers/miner.hh \
    workers/stonemason.hh \
    workers/trainedworker.h

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

FORMS += \
    graphics/dialoggameend.ui \
    graphics/dialoggamestart.ui \
    mapwindow.ui

RESOURCES += \
    resources.qrc
