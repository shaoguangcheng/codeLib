cc=gcc
CXX=g++

OPENCV_CFLAGS = -I/opt/opencv-2.4.5/include/opencv \
		-I/opt/opencv-2.4.5/include
OPENCV_LIBS   = -L/opt/opencv-2.4.5/lib -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab

LEMON_CFLAGS  = -I/opt/lemon/include
LEMON_LIBS = -L/opt/lemon/lib -lemon -lglpk

ALL_CFLAGS    = $(OPENCV_CFLAGS) -I../src/cv -I../src/sys $(LEMON_CFLAGS)
ALL_LIBS      = $(OPENCV_LIBS) -L../src/cv -lcv_lib -L../src/sys -lsys $(LEMON_LIBS)

src-cxx-all := $(wildcard *.cpp)
obj-all     := $(patsubst %.cpp,%.o,$(src-cxx-all))
bin-all     := $(patsubst %.cpp,%.e,$(src-cxx-all))

all : $(bin-all)

%.e : %.cpp
	$(CXX) $< -o $@ $(ALL_CFLAGS) $(ALL_LIBS)
%.o : %.cpp
	$(CXX) -c $< -o $@ $(ALL_CFLAGS) $(ALL_LIBS)
clean:
	rm -rf *.o *.e


