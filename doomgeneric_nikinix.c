#include "doomgeneric.h"
#include "doomkeys.h"

// Exemplo de inclusão das funções/primitivas do Nikinix
// Substitua pelos headers reais do Nikinix (vga/framebuffer, ps2/keyboard, timer)
#include "drivers/framebuffer.h"
#include "drivers/keyboard.h"
#include "drivers/timer.h"

// Resolução padrão do doomgeneric (320x200)
#define DOOM_WIDTH 320
#define DOOM_HEIGHT 200

/**
 * 1. Inicialização do Hardware/OS
 */
void DG_Init(void) {
    // Inicialize o framebuffer ou modo gráfico se o Nikinix já não o fez
    // Exemplo: fb_init(320, 200, 32);
}

/**
 * 2. Atualização do Frame (Renderização)
 * DG_ScreenBuffer contém os pixels do jogo em formato ARGB/XRGB (32-bit).
 */
void DG_DrawFrame(void) {
    uint32_t *src = (uint32_t *)DG_ScreenBuffer;

    // Copia o buffer de 320x200 para a memória de vídeo do Nikinix
    for (int y = 0; y < DOOM_HEIGHT; y++) {
        for (int x = 0; x < DOOM_WIDTH; x++) {
            uint32_t pixel = src[y * DOOM_WIDTH + x];
            
            // Caso o Nikinix use um buffer direto de vídeo (Linear Framebuffer)
            // nikinix_put_pixel(x, y, pixel);
        }
    }
    
    // Se o Nikinix utilizar Double Buffering, force o swap/flush aqui:
    // nikinix_gfx_swap_buffers();
}

/**
 * 3. Leitura de Tempo (Milissegundos)
 * O jogo precisa calcular o Delta Time do loop principal.
 */
uint32_t DG_GetTicksMs(void) {
    // Retorne os ticks do PIT/APIC em milissegundos
    // Exemplo: return nikinix_get_system_time_ms();
    return 0; 
}

/**
 * 4. Mapeamento e Captura de Input (Teclado)
 */
int DG_GetKey(int *pressed, unsigned char *doomKey) {
    // Exemplo de leitura de scancodes PS/2 ou caracteres do buffer do Nikinix
    if (!nikinix_has_key_event()) {
        return 0; // Nenhum evento pendente
    }

    uint8_t scancode = nikinix_read_scancode();
    *pressed = !(scancode & 0x80); // Bit 7 define se foi Pressionado (0) ou Solto (1)
    
    uint8_t key = scancode & 0x7F;

    // Mapeamento de Scancodes PS/2 padrão para as constantes do doomgeneric
    switch (key) {
        case 0x1C: *doomKey = KEY_ENTER; break;
        case 0x01: *doomKey = KEY_ESCAPE; break;
        case 0x48: *doomKey = KEY_UPARROW; break;
        case 0x50: *doomKey = KEY_DOWNARROW; break;
        case 0x4B: *doomKey = KEY_LEFTARROW; break;
        case 0x4D: *doomKey = KEY_RIGHTARROW; break;
        case 0x1D: *doomKey = KEY_FIRE; break;      // LCtrl
        case 0x39: *doomKey = KEY_USE; break;       // Espaço
        case 0x2A: *doomKey = KEY_RSHIFT; break;    // LShift (Run)
        default:
            // Mapeia letras/números comuns se legíveis
            *doomKey = nikinix_scancode_to_ascii(key);
            break;
    }

    return 1; // Retorna 1 informando que processou uma tecla
}

/**
 * 5. Delay do Loop
 */
void DG_SleepMs(uint32_t ms) {
    // Pequena pausa para economizar CPU se necessário
    // nikinix_sleep(ms);
}