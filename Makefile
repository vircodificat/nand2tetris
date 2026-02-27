all: run

run: build
	./tb

build:
	vir compile src/top.vir
	iverilog tb.v build/* -o tb

wave: build
	./tb || exit 0
	gtkwave vars.gtkw

clean:
	rm -rf build/
	rm -f tb
	

.PHONY: all clean build wave
