
#include <cx16.h>
#include <stdio.h>
#include <stdint.h>
#include "vera.h"

void __fastcall__ clear_screen(void);

#define POKE_PIXEL(bank, addr, data) do { \
    *(char*)0x9f25 &= ~1; \
    *(char*)0x9f20 = ((unsigned char)((addr) & 0xFF)); \
    *(char*)0x9f21 = ((unsigned char)(((addr) >> 8))); \
    *(char*)0x9f22 = VERA_INC_0 | (bank); \
    *(char*)0x9f23 = (data); \
} while (0)

// (y << 7) + (y << 5) must be changed accordingly if using 320x240 mode or even 640x480

#define SET_PIXEL(x1, y1, c) POKE_PIXEL(0, (y1 << 7) + (y1 << 5) + x1, c);

void main() {
	uint16_t i;

    VERA.control = 0;
    VERA.display.video |= LAYER1_ENABLED;
    VERA.display.hscale = SCALE_4x;
    VERA.display.vscale = SCALE_4x;
    VERA.layer0.config = 0x0;  // Disable Layer 0
    VERA.layer1.config = LAYER_CONFIG_8BPP | LAYER_CONFIG_BITMAP ;         	// 128x64 map, color depth 1
    VERA.layer1.mapbase = MAP_BASE_ADDR(0x0);                               // Map base at 0x00000
    VERA.layer1.tilebase = 0;  												// Tile base at 0x10000, 8x8 tiles
    videomode(VIDEOMODE_40x30);
    
	clear_screen();

	for (i = 0; i <=10; i++)
		SET_PIXEL(i, i, 3);

    return;
}