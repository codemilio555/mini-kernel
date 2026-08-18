#include "print.h"
#include "stdkernel.h"
#include "stdint.h"

volatile unsigned char *video = (char *)0xB8000;

int write_pos = 0;

void set_cursor(int argPos)
{

    int pos = argPos - 1;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void print(char *valueCh)
{   
    unsigned char *value = (unsigned char*)valueCh;

    for (int i = 0; value[i] != 0; i++)
    {
        if (value[i] == '\n')
        {
            //*2 beacause we have color and char
            write_pos = write_pos - write_pos % 80 + (SCREEN_WIDTH * 2);
            continue;
        }
        // go back  to start of line
        if (value[i] == '\r')
        {
            write_pos = write_pos - write_pos % 80;
            continue;
        }
        // printing char
        video[write_pos] = value[i];
        write_pos++;
        // printing color(white/lightgrey)
        video[write_pos] = 0x0F;
        write_pos++;
    }

    
        set_cursor(write_pos/2);

}
