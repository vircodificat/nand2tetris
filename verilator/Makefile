VERILATOR_ROOT := $(shell verilator --getenv VERILATOR_ROOT)

verilator_compile: build
	verilator \
		--cc \
		-Mdir build/verilator \
		-Ibuild \
		--top-module Cpu \
		build/*.v

verilator_build_add: compile
	@echo $(VERILATOR_ROOT)
	g++ \
		-I/home/vircodificat/.local/verilator/share/verilator/include/ \
		-Ibuild/verilator \
		-lpthread \
		build/verilator/*.cpp \
		$(VERILATOR_ROOT)/include/verilated.cpp \
		$(VERILATOR_ROOT)/include/verilated_threads.cpp \
		verilator/test_add.cpp \
		-o build/verilator/test_add

verilator_test_add: verilator_build_add
	build/verilator/test_add
