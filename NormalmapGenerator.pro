QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NormalmapGenerator
TEMPLATE = app

QMAKE_CXXFLAGS += -fopenmp -std=c++11
LIBS += -fopenmp

SOURCES += src_viewer/main.cpp\
        src_gui/mainwindow.cpp \
    src_generators/intensitymap.cpp \
    src_generators/normalmapgenerator.cpp \
    src_generators/specularmapgenerator.cpp \
    src_gui/graphicsscene.cpp \
    src_gui/graphicsview.cpp \
    src_gui/queueitem.cpp \
    src_gui/queuemanager.cpp \
    src_generators/gaussianblur.cpp \
    src_generators/boxblur.cpp \
    src_generators/ssaogenerator.cpp \
    src_gui/listwidget.cpp \
    src_viewer/camera.cpp \
    src_viewer/light.cpp \
    src_viewer/scene.cpp \
    src_viewer/transform.cpp \
    src_viewer/window.cpp

HEADERS  += src_gui/mainwindow.h \
    src_generators/intensitymap.h \
    src_generators/normalmapgenerator.h \
    src_generators/specularmapgenerator.h \
    src_gui/graphicsscene.h \
    src_gui/graphicsview.h \
    src_gui/queueitem.h \
    src_gui/queuemanager.h \
    src_generators/gaussianblur.h \
    src_generators/boxblur.h \
    src_generators/ssaogenerator.h \
    src_gui/listwidget.h \
    src_gui/clickablelabel.h \
    src_viewer/camera.h \
    src_viewer/light.h \
    src_viewer/scene.h \
    src_viewer/transform.h \
    src_viewer/vertex.h \
    src_viewer/window.h

FORMS    += src_gui/mainwindow.ui

RESOURCES += \
    resource.qrc
