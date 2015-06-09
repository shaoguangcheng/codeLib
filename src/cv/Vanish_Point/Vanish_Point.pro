#-------------------------------------------------
#
# Project created by QtCreator 2013-03-28T15:54:12
#
#-------------------------------------------------

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += __STDC_CONSTANT_MACROS

INCLUDEPATH += \
    /opt/opencv-2.4.5/include/opencv /opt/opencv-2.4.5/include \
    /opt/ffmpeg-1.0/include

LIBS += \
    -L/opt/opencv-2.4.5/lib \
    -lopencv_calib3d -lopencv_contrib -lopencv_core \
    -lopencv_features2d -lopencv_flann \
    -lopencv_highgui -lopencv_imgproc -lopencv_legacy \
    -lopencv_ml -lopencv_nonfree -lopencv_objdetect \
    -lopencv_photo -lopencv_stitching -lopencv_ts \
    -lopencv_video -lopencv_videostab \
    -L/opt/ffmpeg-1.0/lib \
    -lavcodec -lswscale -lavutil \
    -lSDL -lz -lpthread

SOURCES += \
    ./vp.cpp\
    ./cluster.cpp
HEADERS +=  \
    ./cluster.h
