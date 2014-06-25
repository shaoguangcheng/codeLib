CXX=g++
CC=gcc
AR=ar

src-all-cc := $(wildcard *.cc)
inc-all    := $(wildcard *.h)
obj-all    := $(patsubst %.cc,%.o,$(src-all-cc))

tatget := libgnuplot.a

libgnuplot.a : $(obj-all) $(inc-all)
	$(AR) rcs $@ $(obj-all)
%.o : %.cc
	$(CC) -c $< -o $@

clear:
	rm -rf *.o *.a

