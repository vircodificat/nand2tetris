VERILATOR_ROOT := $(shell verilator --getenv VERILATOR_ROOT)

build/verilator/verilated.o: build
	mkdir -p build/verilator
	g++ \
		$(VERILATOR_ROOT)/include/verilated.cpp \
		-c \
		-o build/verilator/verilated.o

build/verilator/verilated_threads.o:
	mkdir -p build/verilator
	g++ \
		$(VERILATOR_ROOT)/include/verilated_threads.cpp \
		-c \
		-o build/verilator/verilated_threads.o

verilator_compile: build $(VIR_SOURCES)
	verilator \
		--cc \
		-Mdir build/verilator \
		verilator/dpi.cpp \
		-Ibuild \
		--top-module Cpu \
		build/*.v

#verilator_build_add: compile
#	g++ \
#		-I$(VERILATOR_ROOT)/include/ \
#		-Ibuild/verilator \
#		-lpthread \
#		build/verilator/*.cpp \
#		$(VERILATOR_ROOT)/include/verilated.cpp \
#		$(VERILATOR_ROOT)/include/verilated_threads.cpp \
#
#		verilator/hack.cpp \
#		verilator/test_add.cpp \
#		-o build/verilator/test_add
#
#verilator_test_add: verilator_build_add
#	build/verilator/test_add

verilator_main: \
	verilator_compile \
	build/verilator/verilated.o \
	build/verilator/verilated_threads.o
	g++ \
		-Wno-format-zero-length \
		-g \
		-I$(VERILATOR_ROOT)/include/ \
		-I$(VERILATOR_ROOT)/include/vltstd/ \
		build/verilator/verilated.o \
		build/verilator/verilated_threads.o \
		-Ibuild/verilator \
		build/verilator/*.cpp \
		verilator/hack.cpp \
		verilator/main.cpp \
		verilator/dpi.cpp \
		-lSDL2 \
		-O2 \
		-o build/verilator/main
