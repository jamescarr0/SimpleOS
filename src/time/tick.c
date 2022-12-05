#include <stdint.h>
#include "time/tick.h"

int g_pit_ticks = 0;

void init_PIT()
{
    uint16_t freq = PIT_MAX_SIGNAL / 100;   // Sets to 100 Hz.
    outb(0x43, 0x36);           // Set our command byte 0x36 */
    outb(0x40, freq);           // Set low byte of freq */
    outb(0x40, freq >> 8);      // Set high byte of freq */
}

void handle_tick()
{
    g_pit_ticks++;
}
