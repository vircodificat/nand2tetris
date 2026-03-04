#include "hack.h"
#include <SDL2/SDL.h>
#include <stdio.h>

static void load_rom() {
//    rom[0] = 0x0002;
//    rom[1] = 0xec10;
//    rom[2] = 0x0003;
//    rom[3] = 0xe090;
//    rom[4] = 0x0000;
//    rom[5] = 0xe308;

    ram[0] = 100;

    rom[0] = 0b0000000000000000;
    rom[1] = 0b1111110000010000;
    rom[2] = 0b0000000000010111;
    rom[3] = 0b1110001100000110;
    rom[4] = 0b0000000000010000;
    rom[5] = 0b1110001100001000;
    rom[6] = 0b0100000000000000;
    rom[7] = 0b1110110000010000;
    rom[8] = 0b0000000000010001;
    rom[9] = 0b1110001100001000;
    rom[10] = 0b0000000000010001;
    rom[11] = 0b1111110000100000;
    rom[12] = 0b1110111010001000;
    rom[13] = 0b0000000000010001;
    rom[14] = 0b1111110000010000;
    rom[15] = 0b0000000000100000;
    rom[16] = 0b1110000010010000;
    rom[17] = 0b0000000000010001;
    rom[18] = 0b1110001100001000;
    rom[19] = 0b0000000000010000;
    rom[20] = 0b1111110010011000;
    rom[21] = 0b0000000000001010;
    rom[22] = 0b1110001100000001;
    rom[23] = 0b0000000000010111;
    rom[24] = 0b1110101010000111;
}

#define SCALE 4

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Hack CPU",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCALE * 512,
        SCALE * 256,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        fprintf(stderr, "Window Creation Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        fprintf(stderr, "Renderer Creation Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    hack_setup();
    load_rom();
    hack_reset();

    int running = 1;
    SDL_Event event;

    while (running) {
        hack_tick();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                SDL_Keycode key = event.key.keysym.sym;

                if (key == SDLK_ESCAPE) {
                    running = 0;
                } else {
                    printf("Key pressed: %s (code: %d)\n", SDL_GetKeyName(key), key);
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (int row = 0; row < 256; row++) {
            for (int col = 0; col < 512; col++) {
                uint16_t addr = MEM_SCR + 32 * row + col / 16;
                uint16_t value = (hack_read_ram(addr) >> (col % 16)) & 1;

                if (value) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                } else {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                }

                for (int i = 0; i < SCALE; i++) {
                    for (int j = 0; j < SCALE; j++) {
                        SDL_RenderDrawPoint(renderer, SCALE * col + i, SCALE * row + j);
                    }
                }
            }
        }

        SDL_RenderPresent(renderer);
    }

    hack_shutdown();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
