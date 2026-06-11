QT       += core gui widgets

CONFIG += c++17

#INCLUDEPATH += "C:/TPU/sem4/programming_technologies/DLL"
INCLUDEPATH += "$$PWD/../DLL"
#LIBS += -L"C:/TPU/sem4/programming_technologies/DLL/build" -lMinesweeperLogic
LIBS += -L"$$PWD/../DLL/build" -lMinesweeperLogic

SOURCES += \
    cellbutton.cpp \
    gamecontroller.cpp \
    mainwindow.cpp \
    main.cpp \
    gamesetupdialog.cpp \
    endgamedialog.cpp

HEADERS += \
    cellbutton.h \
    gamecontroller.h \
    mainwindow.h \
    gamesetupdialog.h \
    endgamedialog.h

FORMS += \
    mainwindow.ui \
    gamesetupdialog.ui \
    endgamedialog.ui

DLL_SOURCE_PATH = "C:/TPU/sem4/programming_technologies/DLL/build/MinesweeperLogic.dll"

FIXED_SOURCE = $$replace(DLL_SOURCE_PATH, /, \\)
FIXED_DEST   = $$replace(OUT_PWD, /, \\)


QMAKE_POST_LINK += $(COPY_FILE) \"$$FIXED_SOURCE\" \"$$FIXED_DEST\"