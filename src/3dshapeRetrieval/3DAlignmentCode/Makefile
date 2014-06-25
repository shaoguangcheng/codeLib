CC=gcc
CXX=g++

################################################################################
# OpenCV settings
# run following command first:
#   EXPORT PKG_CONFIG_PATH=/opt/OpenCV-2.4/lib/pkgconfig
################################################################################
OPENCV_CFLAGS = -I/opt/opencv-2.4.5/include/opencv\
	-I/opt/opencv-2.4.5/include
OPENCV_LIBS   = -L/opt/opencv-2.4.5/lib \
    -lopencv_calib3d -lopencv_contrib -lopencv_core \
    -lopencv_features2d -lopencv_flann\
    -lopencv_highgui -lopencv_imgproc -lopencv_legacy \
    -lopencv_ml -lopencv_nonfree -lopencv_objdetect \
    -lopencv_photo -lopencv_stitching -lopencv_ts \
    -lopencv_video -lopencv_videostab

################################################################################
# OpenGL settings
################################################################################
OPENGL_CFLAGS = 
OPENGL_LIBS   = -lGL -lGLU -lglut

################################################################################
# FFTW settings
################################################################################
FFTW_CFLAGS = -I../../../3dpart/fftw
FFTW_LIBS   = -L../../../3dpart/fftw -lfftw


################################################################################
# Overall settings
################################################################################
ALL_CFLAGS = $(OPENCV_CFLAGS) $(OPENGL_CFLAGS) $(FFTW_CFLAGS)
ALL_LIBS   = $(OPENCV_LIBS)   $(OPENGL_LIBS)   $(FFTW_LIBS)


src-cxx-all := $(wildcard *.cpp)
src-c-all := $(wildcard *.c)
bin-all := $(patsubst %.cpp,%.e,$(src-cxx-all)) $(patsubst %.c,%.e,$(src-c-all))
obj-all := $(patsubst %.cpp,%.o,$(src-cxx-all)) $(patsubst %.c,%.o,$(src-c-all))



all : lfd.e

lfd.e : $(obj-all)
	$(CXX) -o $@ $? $(ALL_LIBS)

%.e:%.cpp
	$(CXX) $< -o $@ $(ALL_CFLAGS) $(ALL_LIBS)

%.e:%.c
	$(CXX) $< -o $@ $(ALL_CFLAGS) $(ALL_LIBS)

%.o:%.cpp
	$(CXX) -c $< -o $@ $(ALL_CFLAGS)

%.o:%.c
	$(CXX) -c $< -o $@ $(ALL_CFLAGS)

clean :
	rm -f *.e *.o

