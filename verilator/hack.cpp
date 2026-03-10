#include "hack.h"
#include "stdio.h"

#include "verilated.h"
#include "VCpu.h"

#define DEBUG 0
#define LOG(...) if (DEBUG) { printf(__VA_ARGS__); }

#define MEM_DEBUG 0
#define MEM_LOG(...) if (MEM_DEBUG) { printf(__VA_ARGS__); }

VCpu CPU;
uint16_t rom[16384];
uint16_t ram[16384];
uint16_t screen[0x2000];
uint32_t cycle = 0;

void hack_setup() {
    Verilated::commandArgs(0, (char**)NULL);

    // Clear screen
    for (int i = 0; i < 0x2000; i++) {
        screen[i] = 0x0000;
    }
}

void hack_shutdown() {
}

void hack_tick() {
    LOG("--------------------\n");
    LOG("TICK %d\n", cycle);

    // clock low
    CPU.clock = 0;
    CPU.eval();

    // clock high
    CPU.clock = 1;

    CPU.instruction = rom[CPU.pc];
    CPU.memory_in = hack_read_ram(CPU.memory_addr);
    CPU.eval();

    LOG("pc           = %04x\n", CPU.pc);
    LOG("rom[%04x] = %04x\n",    CPU.pc, rom[CPU.pc]);
    LOG("memory_addr  = %04x\n", CPU.memory_addr);
    LOG("ram[%04x] = %04x\n",    CPU.memory_addr, hack_read_ram(CPU.memory_addr));

    LOG("memory_out   = %04x\n", CPU.memory_out);
    LOG("memory_write = %d\n",   CPU.memory_write);

    if (CPU.memory_write) {
        hack_write_ram(CPU.memory_addr, CPU.memory_out);
        LOG("ram[%04x] = %04x\n", CPU.memory_addr, hack_read_ram(CPU.memory_addr));
    }

    LOG("\n");
    cycle++;
}

void hack_reset() {
    LOG("--------------------\n");
    LOG("RESET\n");
    CPU.reset = 1;

    // clock low
    CPU.clock = 0;
    CPU.eval();

    // clock high
    CPU.clock = 1;
    CPU.eval();

    CPU.reset = 0;

    LOG("pc          = %04x\n", CPU.pc);
    LOG("rom[%04x] = %04x\n", CPU.pc, rom[CPU.pc]);
    LOG(" ");
}

uint16_t hack_read_ram(uint16_t addr) {
    if (addr < MEM_SCR) {
        return ram[addr];
    } else if (addr < MEM_KBD) {
        return screen[addr - MEM_SCR];
    } else {
        return 0xffff;
    }
}

void hack_write_ram(uint16_t addr, uint16_t value) {
    if (addr < MEM_SCR) {
        MEM_LOG("Write to RAM: %04x set to %04x\n", addr, value);
        ram[addr] = value;
    } else if (addr < MEM_KBD) {
        MEM_LOG("Write to SCR: %04x set to %04x\n", addr, value);
        screen[addr - MEM_SCR] = value;
    } else {
        MEM_LOG("Write KBD: %04x set to %04x\n", addr, value);
        // DO NOTHING FOR KBD
    }
}
