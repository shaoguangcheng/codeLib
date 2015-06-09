TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /opt/opencv-2.4.5/include/opencv  /opt/opencv-2.4.5/include
LIBS   += -L/opt/opencv-2.4.5/lib -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d\
 -lopencv_flann -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree \
-lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab


SOURCES += \
        ./CompressiveTracker.cpp \
        ./RunTracker.cpp

HEADERS += \
        ./CompressiveTracker.h

