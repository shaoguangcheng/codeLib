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
    -lopencv_features2d -lopencv_flann -lopencv_gpu \
    -lopencv_highgui -lopencv_imgproc -lopencv_legacy \
    -lopencv_ml -lopencv_nonfree -lopencv_objdetect \
    -lopencv_photo -lopencv_stitching -lopencv_ts \
    -lopencv_video -lopencv_videostab \
    -L/opt/ffmpeg-1.0/lib \
    -lavcodec -lswscale -lavutil \
    -lSDL -lz -lpthread \
    -L/opt/l_cc_11.0.083/lib/intel64 \
    -L/opt/l_mkl_11.1.059/lib/em64t


SOURCES += \
    ./color_reco.cpp\
    ./CRawImage.cpp\
    ./CRecognition.cpp

HEADERS += \
    ./CRawImage.h\
    ./CRecognition.h \
    color_reco.h
