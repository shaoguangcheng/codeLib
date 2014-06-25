cc=gcc
CXX=g++
AR=ar

OPENCV_CFLAGS = -I/opt/opencv-2.4.5/include/opencv -I/opt/opencv-2.4.5/include
OPENCV_LIBS   = -L/opt/opencv-2.4.5/lib -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab

ALL_CFLAGS    = $(OPENCV_CFLAGS)
ALL_LIBS      = $(OPENCV_LIBS)

src-cxx-all := $(wildcard *.cpp)
inc-all     := $(wildcard *.h)
obj-all     := $(patsubst %.cpp,%.o,$(src-cxx-all))
bin-all     := $(patsubst %.cpp,%.e,$(src-cxx-all))

target := libsys.a

$(target):$(obj-all) $(inc-all)
	$(AR) rcs $@ $(obj-all)

%.e : %.cpp
	$(CXX) $< -o $@ $(ALL_CFLAGS) $(ALL_LIBS)
%.o : %.cpp
	$(CXX) -c $< -o $@ $(ALL_CFLAGS)
clean:
	rm -rf *.o *.e *.a


