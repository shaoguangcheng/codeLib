CC=gcc
CXX=g++
AR=ar

OPENCV_CFLAGS = $(shell pkg-config --cflags opencv)
OPENCV_LIBS   = $(shell pkg-config --libs opencv)

INSTALL_DIR=./bin
TARGET=test
MYLIB=lib.a

src-cxx-all := $(wildcard *.cpp)
src-c-all := $(wildcard *.c)
bin-all := $(patsubst %.cpp,%.e,$(src-cxx-all)) $(patsubst %.c,%.e,$(src-c-all))
obj-all := $(patsubst %.cpp,%.o,$(src-cxx-all)) $(patsubst %.c,%.o,$(src-c-all))

all : $(TARGET)

#$(TARGET) : $(obj-all)
#	$(CXX) -o $@ $< $(OPENCV_LIBS)
$(TARGET) : $(MYLIB)
	$(CXX) -o $@ test.cpp $< 
$(MYLIB) : $(obj-all)
	$(AR) rcs $@ $<
	rm *.o
%.e : %.cpp
	$(CXX) -o $@ $< $(OPENCV_LIBS) $(OPENCV_CFLAGS)
%.e : %.c
	$(CXX) -o $@ $< $(OPENCV_LIBS) $(OPENCV_CFLAGS)
%.o : %.c
	$(CXX) -o $@ -c $< $(OPENCV_CFLAGS)
%.o : %.cpp
	$(CXX) -o $@ -c $< $(OPENCV_CFLAGS)

clean:
	-rm *.e *.o *.a $(TARGET)

install : $(TARGET)
	@if [ -d $(INSTALL_DIR) ];\
	then\
		cp $(TARGET) $(INSTALL_DIR);\
		chmod +x $(INSTALL_DIR)/$(TARGET);\
		echo "$(TARGET) installed in $(INSTALL_DIR)";\
	else\
		mkdir $(INSTALL_DIR);\
		echo "$(INSTALL_DIR) has been created";\
	fi

# DO NOT DELETE
