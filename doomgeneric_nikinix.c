/*
    CODED BY Danoni631, on 09/01/2026

    A DOOM generic port for Nikinix

    If you want to use this port GIVE CREDIT TO ME

    And if this port gonna be added in Nikinix, need the other DOOM generic source files
*/


// DOOM headers
#include "doomgeneric.h"
#include "doomkeys.h"

// Nikinix headers
#include "drivers/framebuffer.h"
#include "drivers/keyboard.h"
#include "drivers/timer.h"

// Resolution 320x200
#define DOOM_WIDTH 320
#define DOOM_HEIGHT 200

/**
 * Init OS Hardware
 */
void DG_Init(void)
{
    // Start framebuffer
    fb_init(320, 200, 32); // Remove this if framebuffer was inited
}

/**
 * Frame update
 */
void DG_DrawFrame(void)
{
    uint32_t *src = (uint32_t *)DG_ScreenBuffer;

    for (int y = 0; y < DOOM_HEIGHT; y++)
    {
        for (int x = 0; x < DOOM_WIDTH; x++)
        {
            uint32_t pixel = src[y * DOOM_WIDTH + x];
            // nikinix_put_pixel(x, y, pixel);
        }
    }

    // nikinix_gfx_swap_buffers();
}

/**
    Time read system
    :D
 */
uint32_t DG_GetTicksMs(void)
{
    // Example: return nikinix_get_system_time_ms();
    return 0; 
}

/**
 * Keyboard map
 */
int DG_GetKey(int *pressed, unsigned char *doomKey)
{
    if (!nikinix_has_key_event())
    {
        return 0;
    }

    uint8_t scancode = nikinix_read_scancode();
    *pressed = !(scancode & 0x80);
    
    uint8_t key = scancode & 0x7F;

    // Mapeamento de Scancodes PS/2 padrão para as constantes do doomgeneric
    switch (key)
    {
        case 0x1C: *doomKey = KEY_ENTER; break; // Enter
        case 0x01: *doomKey = KEY_ESCAPE; break; // Esc
        case 0x48: *doomKey = KEY_UPARROW; break; // W
        case 0x50: *doomKey = KEY_DOWNARROW; break; // S
        case 0x4B: *doomKey = KEY_LEFTARROW; break; // A
        case 0x4D: *doomKey = KEY_RIGHTARROW; break; / D
        case 0x1D: *doomKey = KEY_FIRE; break;      // LCtrl
        case 0x39: *doomKey = KEY_USE; break;       // Space
        case 0x2A: *doomKey = KEY_RSHIFT; break;    // LShift (Run)
        
        default:
            *doomKey = nikinix_scancode_to_ascii(key);
            break;
    }

    return 1;
}

/**
 * 5. Delay
 */
void DG_SleepMs(uint32_t ms)
{
    // nikinix_sleep(ms); // If was necessary, use this
}
