#include <stdio.h>
#include <stdint.h>
#include "svdpi.h"

#include "hack.h"
#include <stdlib.h>

#define EXTRACT16(v) (v[0].aval & 0xffff)

extern "C" void monitor(
    const svLogicVecVal* pc,
    const svLogicVecVal* instr,
    const svLogicVecVal* a,
    const svLogicVecVal* d,
    const svLogicVecVal* m
) {
    printf("PC %04x\n", EXTRACT16(pc));
    printf("INSTR %04x\n", EXTRACT16(instr));

    printf("A  %04x\n", EXTRACT16(a));
    printf("D  %04x\n", EXTRACT16(d));
    printf("M  %04x\n", EXTRACT16(m));
    puts("");
}
