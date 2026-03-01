#include "hack.h"
#include "stdio.h"

#include "verilated.h"
#include "VCpu.h"

VCpu CPU;
uint16_t rom[16384];
uint16_t ram[16384];
uint32_t cycle = 0;

void hack_setup() {
    Verilated::commandArgs(0, (char**)NULL);
}

void hack_shutdown() {
}

void hack_tick() {
    printf("--------------------\n");
    printf("TICK %d\n", cycle);

    // clock low
    CPU.clock = 0;
    CPU.eval();

    // clock high
    CPU.clock = 1;

    CPU.instruction = rom[CPU.pc];
    CPU.memory_in = hack_read_ram(CPU.memory_addr);
    CPU.eval();

    printf("pc           = %04x\n", CPU.pc);
    printf("rom[%04x] = %04x\n",    CPU.pc, rom[CPU.pc]);
    printf("memory_addr  = %04x\n", CPU.memory_addr);
    printf("ram[%04x] = %04x\n",    CPU.memory_addr, hack_read_ram(CPU.memory_addr));

    printf("memory_out   = %04x\n", CPU.memory_out);
    printf("memory_write = %d\n",   CPU.memory_write);

    if (CPU.memory_write) {
        ram[CPU.memory_addr] = CPU.memory_out;
        printf("ram[%04x] = %04x\n", CPU.memory_addr, hack_read_ram(CPU.memory_addr));
    }

    puts("");
    cycle++;
}

void hack_reset() {
    printf("--------------------\n");
    printf("RESET\n");
    CPU.reset = 1;

    // clock low
    CPU.clock = 0;
    CPU.eval();

    // clock high
    CPU.clock = 1;
    CPU.eval();

    CPU.reset = 0;

    printf("pc          = %04x\n", CPU.pc);
    printf("rom[%04x] = %04x\n", CPU.pc, rom[CPU.pc]);
    puts("");
}

uint16_t hack_read_ram(uint16_t addr) {
    if (addr < MEM_SCR) {
        return ram[addr];
    } else if (addr < MEM_KBD) {
        return 0xaeae;
    } else {
        return 0xffff;
    }
}

void hack_write_ram(uint16_t addr, uint16_t value) {
    if (addr < MEM_SCR) {
        ram[addr] = value;
    } else if (addr < MEM_KBD) {
        printf("Write to screen: %04x set to %04x\n", addr, value);
    } else {
        // DO NOTHING FOR KBD
    }
}
