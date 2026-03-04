#include "hack.h"
#include "assert.h"

static void load_rom() {
    rom[0] = 0x0002;
    rom[1] = 0xec10;
    rom[2] = 0x0003;
    rom[3] = 0xe090;
    rom[4] = 0x0000;
    rom[5] = 0xe308;
}

int main(int argc, char** argv) {
    load_rom();

    hack_setup();
    hack_reset();
    hack_tick();

    for (int i = 0; i < 7; i++)
        hack_tick();

    assert(hack_read_ram(0) == 5);

    hack_shutdown();

    return 0;
}
