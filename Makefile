all:
	vir compile src/arithmetic.vir
	iverilog tb.v build/* -o build/tb
	./build/tb

wave: all
	gtkwave alu.vcd 
