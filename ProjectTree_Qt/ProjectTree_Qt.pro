QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

LIBS += -L"lib\SFML_MinGW\lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release):   LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH +=              \
    include/                \
    include/Core/           \
    include/Widgets/        \
    lib/SFML_MinGW/include/ \
    lib/                    \

DEPENDPATH += \
    SFML_MinGW/include

HEADERS += \
    include/Common.h \
    include/Core/Animation.h \
    include/Core/AnimationManager.h \
    include/Core/Entity.h \
    include/Core/EntityFactory.h \
    include/Core/EntityManager.h \
    include/Core/Explover.h \
    include/Core/ExploverVer1.0.h \
    include/Core/GameApplication.h \
    include/Core/InputController.h \
    include/Core/LevelManager.h \
    include/Core/LoadingManager.h \
    include/Core/Object.h \
    include/Core/Settings.h \
    include/Core/Timer.h \
    include/Core/TmxLevel.h \
    include/Defines.h \
    include/Widgets/QSFMLCanvas.h \
    include/mainwindow.h

SOURCES += \
    src/Common.cpp \
    src/Core/Animation.cpp \
    src/Core/AnimationManager.cpp \
    src/Core/Entity.cpp \
    src/Core/EntityFactory.cpp \
    src/Core/EntityManager.cpp \
    src/Core/Explover.cpp \
    src/Core/GameApplication.cpp \
    src/Core/InputController.cpp \
    src/Core/LevelManager.cpp \
    src/Core/LoadingManager.cpp \
    src/Core/Object.cpp \
    src/Core/Settings.cpp \
    src/Core/TmxLevel.cpp \
    src/Widgets/QSFMLCanvas.cpp \
    src/main.cpp \
    src/mainwindow.cpp \

FORMS += \
    ui/mainwindow.ui

configfiles.path = $$OUT_PWD/lib
configfiles.files = $$PWD/lib/*
COPIES += configfiles

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target






