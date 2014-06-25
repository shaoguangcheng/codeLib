cc=gcc
CXX=g++
AR=ar

#FFMPEG_CFLAGS = -I/opt/ffmpeg-1.0/include
#FFMPEG_LIBS   = -L/opt/ffmpeg-1.0/lib -lavcodec -lswscale -lavutil -lavfilter -lavformat -ldl -lasound -lSDL -lx264 -lmp3lame -lm -pthread -lbz2 -lz -lrt 

BOOST_LIBS  = -lboost_date_time -lboost_date_time-mt -lboost_filesystem -lboost_filesystem-mt -lboost_graph -lboost_graph-mt -lboost_iostreams -lboost_iostreams-mt -lboost_math_c99 -lboost_math_c99f -lboost_math_c99f-mt -lboost_math_c99l -lboost_math_c99l-mt -lboost_math_c99-mt -lboost_math_tr1 -lboost_math_tr1f -lboost_math_tr1f-mt -lboost_math_tr1l -lboost_math_tr1l-mt -lboost_math_tr1-mt -lboost_prg_exec_monitor -lboost_prg_exec_monitor-mt -lboost_program_options -lboost_program_options-mt -lboost_regex -lboost_regex-mt -lboost_serialization -lboost_serialization-mt -lboost_signals -lboost_signals-mt -lboost_system -lboost_system-mt -lboost_thread -lboost_thread-mt -lboost_unit_test_framework -lboost_unit_test_framework-mt -lboost_wave -lboost_wave-mt -lboost_wserialization -lboost_wserialization-mt


OPENCV_CFLAGS = -I/opt/opencv-2.4.5/include/opencv -I/opt/opencv-2.4.5/include
OPENCV_LIBS   = -L/opt/opencv-2.4.5/lib -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab

ALL_CFLAGS    = $(OPENCV_CFLAGS) $(FFMPEG_CFLAGS) 
ALL_LIBS      = $(OPENCV_LIBS) $(FFMPEG_LIBS)

src-cxx-all := $(wildcard *.cpp)
inc-all     := $(wildcard *.h)
obj-all     := $(patsubst %.cpp,%.o,$(src-cxx-all))
bin-all     := $(patsubst %.cpp,%.e,$(src-cxx-all))

target := libcv_lib.a

$(target):$(obj-all) $(inc-all)
	$(AR) rcs $@ $(obj-all)

%.e : %.cpp
	$(CXX) $< -o $@ $(ALL_CFLAGS) $(ALL_LIBS)
%.o : %.cpp
	$(CXX) -c $< $(ALL_CFLAGS) $(ALL_LIBS) -o $@ 
clean:
	rm -rf *.o *.e *.a


