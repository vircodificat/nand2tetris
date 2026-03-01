#include "stdint.h"

#include "verilated.h"
#include "VCpu.h"


uint32_t cycle = 0;
uint16_t rom[16384];
uint16_t ram[16384];

static void load_rom() {
    rom[0] = 0x0002;
    rom[1] = 0xec10;
    rom[2] = 0x0003;
    rom[3] = 0xe090;
    rom[4] = 0x0000;
    rom[5] = 0xe308;
}

static void tick(VCpu* cpu) {
    printf("--------------------\n");
    printf("TICK %d\n", cycle);

    // clock low
    cpu->clock = 0;
    cpu->eval();

    // clock high
    cpu->clock = 1;

    cpu->instruction = rom[cpu->pc];
    cpu->memory_in = ram[cpu->memory_addr];
    cpu->eval();

    printf("pc           = %04x\n", cpu->pc);
    printf("rom[%04x] = %04x\n",    cpu->pc, rom[cpu->pc]);
    printf("memory_addr  = %04x\n", cpu->memory_addr);
    printf("ram[%04x] = %04x\n",    cpu->memory_addr, ram[cpu->memory_addr]);

    printf("memory_out   = %04x\n", cpu->memory_out);
    printf("memory_write = %d\n",   cpu->memory_write);

    if (cpu->memory_write) {
        ram[cpu->memory_addr] = cpu->memory_out;
        printf("ram[%04x] = %04x\n", cpu->memory_addr, ram[cpu->memory_addr]);
    }

    puts("");
    cycle++;
}

static void reset(VCpu* cpu) {
    printf("--------------------\n");
    printf("RESET\n");
    cpu->reset = 1;

    // clock low
    cpu->clock = 0;
    cpu->eval();

    // clock high
    cpu->clock = 1;
    cpu->eval();

    cpu->reset = 0;

    printf("pc          = %04x\n", cpu->pc);
    printf("rom[%04x] = %04x\n", cpu->pc, rom[cpu->pc]);
    puts("");
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    load_rom();

    VCpu* cpu = new VCpu;
    reset(cpu);
    tick(cpu);

    for (int i = 0; i < 7; i++)
        tick(cpu);

    assert(ram[0] == 5);

    delete cpu;
    return 0;
}
