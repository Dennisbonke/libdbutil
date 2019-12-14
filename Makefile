PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
DIR:=src/

undefine CC
undefine CXX
undefine CPP
undefine CFLAGS
undefine CXXFLAGS
undefine CPPFLAGS

CC:=gcc
CXX:=g++

OBJS = $(DIR)libdbutil.o $(DIR)dblogging.o

CFLAGS=-std=gnu11 -fPIC -Wall -Wextra -g
CXXFLAGS=-std=gnu++11 -fPIC -Wall -Wextra -g
LDFLAGS:=-fPIC -shared -Wl,-soname,libdbutil.so.1
LIBS:=-lc -lm

ifeq ($(BUILD_MODE),debug)
	CFLAGS+=-g
	CXXFLAGS+=-g
else ifeq ($(BUILD_MODE),run)
	CFLAGS+=-O2
	CXXFLAGS+=-O2
else
#	$(error Build mode $(BUILD_MODE) not supported by this Makefile)
endif

all:	build/libdbutil.so.1.0.1

build/libdbutil.so.1.0.1:	$(OBJS)
	mkdir -pv build
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)
	

%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -fr build/libdbutil.so* libdbutil.so* $(OBJS)
	
install: all
	bash install.sh

remove:
	bash remove.sh
