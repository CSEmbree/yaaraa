CC = gcc
CXX = g++
DEBUG = -g
RM = rm -rf
CPPFLAGS = -pthread -Wall -O3 -fPIC -fpermissive -std=c++0x $(DEBUG)
#LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS = -pthread

SRCS=yaaraa.cpp src/audio_recorder.cpp src/config_handler.cpp src/feature_vector.cpp src/json_generator.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: yaaraa

yaaraa: $(OBJS)
	$(CXX) $(DEBUG) -o  $@ $(OBJS) $(LDLIBS) 

#test: -lgtest

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	find . -type f -name '*.o' -delete
	find . -type f -name '*.*~' -delete
	find . -type f -name '\#*#' -delete
