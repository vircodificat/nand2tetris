#include <stdio.h>
#include <stdint.h>
#include "svdpi.h"

#include "hack.h"
#include <stdlib.h>

#define EXTRACT16(v) (v[0].aval & 0xffff)

#define DEBUG 0
#define LOG(...) if (DEBUG) { printf(__VA_ARGS__); }

#include <string>

const char *comp_strs[2][64] = {

    // a = 0
    {
        "D&A",
        "INVALID",
        "D+A",
        "INVALID",
        "INVALID",
        "INVALID",
        "INVALID",
        "A-D",
        "INVALID",
        "INVALID",
        "INVALID",
        "INVALID",
        "D",
        "!D",
        "D-1",
        "-D",
        "INVALID",
        "INVALID",
        "INVALID",
        "D-A",
        "INVALID",
        "D|A",
        "INVALID",
        "INVALID",
        "INVALID",
        "INVALID",
        "INVALID",
        "INVALID",
        "INVALID",
        "INVALID",
        "INVALID",
        "D+1",
        "INVALID",
        "INVALID",
        "INVALID",
        "INVALID",
        "INVALID",
        "INVALID",
        "INVALID",
        "INVALID",
        "INVALID",
        "INVALID",
        "0",
        "INVALID",
        "INVALID",
        "INVALID",
        "INVALID",
        "INVALID",
        "A",
        "!A",
        "A-1",
        "-A",
        "INVALID",
        "INVALID",
        "INVALID",
        "A+1",
        "INVALID",
        "INVALID",
        "-1",
        "INVALID",
        "INVALID",
        "INVALID",
        "INVALID",
        "1"

    },

    // a = 1
    {
        /*000000*/ "D&M",
        /*000001*/ "INVALID",
        /*000010*/ "D+M",
        /*000011*/ "INVALID",
        /*000100*/ "INVALID",
        /*000101*/ "INVALID",
        /*000110*/ "INVALID",
        /*000111*/ "M-D",
        /*001000*/ "INVALID",
        /*001001*/ "INVALID",
        /*001010*/ "INVALID",
        /*001011*/ "INVALID",
        /*001100*/ "INVALID",
        /*001101*/ "INVALID",
        /*001110*/ "INVALID",
        /*001111*/ "INVALID",
        /*010000*/ "INVALID",
        /*010001*/ "INVALID",
        /*010010*/ "INVALID",
        /*010011*/ "D-M",
        /*010100*/ "INVALID",
        /*010101*/ "D|M",
        /*010110*/ "INVALID",
        /*010111*/ "INVALID",
        /*011000*/ "INVALID",
        /*011001*/ "INVALID",
        /*011010*/ "INVALID",
        /*011011*/ "INVALID",
        /*011100*/ "INVALID",
        /*011101*/ "INVALID",
        /*011110*/ "INVALID",
        /*011111*/ "INVALID",
        /*100000*/ "INVALID",
        /*100001*/ "INVALID",
        /*100010*/ "INVALID",
        /*100011*/ "INVALID",
        /*100100*/ "INVALID",
        /*100101*/ "INVALID",
        /*100110*/ "INVALID",
        /*100111*/ "INVALID",
        /*101000*/ "INVALID",
        /*101001*/ "INVALID",
        /*101010*/ "INVALID",
        /*101011*/ "INVALID",
        /*101100*/ "INVALID",
        /*101101*/ "INVALID",
        /*101110*/ "INVALID",
        /*101111*/ "INVALID",
        /*110000*/ "M",
        /*110001*/ "!M",
        /*110010*/ "M-1",
        /*110011*/ "-M",
        /*110100*/ "INVALID",
        /*110101*/ "INVALID",
        /*110110*/ "INVALID",
        /*110111*/ "M+1",
        /*111000*/ "INVALID",
        /*111001*/ "INVALID",
        /*111010*/ "INVALID",
        /*111011*/ "INVALID",
        /*111100*/ "INVALID",
        /*111101*/ "INVALID",
        /*111110*/ "INVALID",
        /*111111*/ "INVALID"
    }
};

const char *dst_strs[] = {
    "",
    "M",
    "D",
    "MD",
    "A",
    "AM",
    "AD",
    "AMD",
};

const char *jmp_strs[] = {
    "",
    "JGT",
    "JEQ",
    "JGE",
    "JLT",
    "JNE",
    "JLE",
    "JMP",
};

void print_opcode(uint16_t instr) {
    int is_c = instr >> 15;

    if (is_c) {
        int a = (instr >> 12) & 0b1;
        int comp_idx = (instr >> 6) & 0b111111;
        int dst_idx = (instr >> 3) & 0b111;
        int jmp_idx = instr & 0b111;

        LOG(
            "%s = %s ; %s\n",
            dst_strs[dst_idx],
            comp_strs[a][comp_idx],
            jmp_strs[jmp_idx]
        );
    } else {
        uint16_t addr = instr & 0b0111111111111111;
        LOG("@%d\n", addr);

    }
}

extern "C" void monitor(
    const svLogicVecVal* pc,
    const svLogicVecVal* instr,
    const svLogicVecVal* a,
    const svLogicVecVal* d,
    const svLogicVecVal* m
) {
    LOG("PC     %04x\n", EXTRACT16(pc));
    LOG("INSTR  %04x\n", EXTRACT16(instr));
    LOG("OPCODE ");
    print_opcode(EXTRACT16(instr));

    LOG("A  %04x\n", EXTRACT16(a));
    LOG("D  %04x\n", EXTRACT16(d));
    LOG("M  %04x\n", EXTRACT16(m));
    LOG("");
}
