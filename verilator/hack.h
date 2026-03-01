#ifndef HACK_H
#define HACK_H

#include "stdint.h"

#define MEM_RAM 0x0000
#define MEM_SCR 0x4000
#define MEM_KBD 0x6000

extern uint16_t rom[16384];
extern uint16_t ram[16384];

void hack_setup();
void hack_shutdown();

void hack_tick();
void hack_reset();

uint16_t hack_read_ram(uint16_t addr);
void hack_write_ram(uint16_t addr, uint16_t value);

#endif
