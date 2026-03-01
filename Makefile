TB = "alu"

BASEDIR := $(CURDIR)

default: run
	@echo "Current dir: $(PWD)"


include verilator/Makefile


run: build
	./build/tb_$(TB)

build:
	vir compile src/top.vir
	iverilog tb/$(TB).v build/*.v -o build/tb_$(TB)

wave: build
	./build/tb_$(TB) || exit 0
	gtkwave gtkw/$(TB).gtkw

clean:
	rm -rf build/

.PHONY: all clean build wave compile
