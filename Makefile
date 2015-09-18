# Please define this in your Makefile
RELATIVE_PATH?=.

# ARDUINO SETTINGS

BOARD_TAG     ?= pro5v328
ARDUINO_PORT  ?= /dev/ttyUSB0

# PC SETTINGS

PC_LDFLAGS?=`pkg-config --libs sdl2` -pthread
PC_CXXFLAGS?=-Wall -DBUILD_PC -I${RELATIVE_PATH}/_submodules/arduino-libs/PolychrHAUM
PC_CXX?=g++

# RULES

SUBMODULES=$(RELATIVE_PATH)/_submodules
ARDUINO_LIBS=FastLED PolychrHAUM
LOCAL_CPP_SRCS=$(wildcard *.cpp [!_]*/*.cpp [!_]*/[!_]*/*.cpp)
USER_LIB_PATH=$(SUBMODULES)/arduino-libs

include $(SUBMODULES)/arduino-mk/Arduino.mk

pc: polychrhaum-pc

polychrhaum-pc:$(patsubst %.cpp,build-pc/%.o,$(LOCAL_CPP_SRCS)) $(patsubst %.ino,build-pc/%.ino.o, $(wildcard *.ino)) ${USER_LIB_PATH}/PolychrHAUM/polychrhaum-pc.a
	${PC_CXX} ${PC_CXXFLAGS} -o $@ $^ ${PC_LDFLAGS}

${USER_LIB_PATH}/PolychrHAUM/polychrhaum-pc.a: force_look
	cd ${USER_LIB_PATH}/PolychrHAUM && ${MAKE} pc ${MFLAGS}

play: polychrhaum-pc
	./polychrhaum-pc

build-pc/%.o:%.cpp $(wildcard *.h **/*.h **/**/*.h)
	@mkdir -p build-pc/$(dir $<)
	${PC_CXX} ${CXXFLAGS} ${PC_CXXFLAGS} -c $< -o $@

build-pc/%.ino.o: %.ino
	@mkdir -p build-pc/$(dir $<)
	${PC_CXX} ${CXXFLAGS} ${PC_CXXFLAGS} -xc++ -c $< -o $@

clean-pc:
	cd ${USER_LIB_PATH}/PolychrHAUM && ${MAKE} clean
	rm -rf build-pc polychrhaum-pc

force_look:
	@true
