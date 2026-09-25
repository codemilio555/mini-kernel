#include "stdkernel.h"
#include "print.h"
static const char kbd_us[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', /* Backspace */
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',  /* Enter */
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' '};
// Mac tastature, I have ony this one
static const char us_keymap_shift[] = {
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '`', 0,
    '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0};

unsigned int is_shift = 1;
int getchar_polling()
{
    while ((inb(0x64) & 0x01) == 0)
    {
        __asm__ volatile("pause");
    }

    int code = inb(0x60);
    /*char buf[10];
    print("\nCode!: ");
    itoa(code, buf);
    print(buf);
    print("\n");*/
    if (code > 128)
    {
        // shift up
        if (code == 182)
        {
            is_shift = 1;
        }
        return getchar_polling();
    }
    // shift
    if (code == 54)
    {
        is_shift = 0;
        return getchar_polling();
    }
    if (is_shift == 0)
    {
        return us_keymap_shift[code];
    }
    return kbd_us[code];
}

// using getchar_polling
void read_input(char *buf, int size)
{
    int at = 0;
    char charnow = (char)getchar_polling();
    while (charnow != '\n' && size > at)
    {
        if (charnow == '\b')
        {
            putchar('\b');
            charnow = (char)getchar_polling();
            at--;
            continue;
        }
        putchar(charnow);
        buf[at] = charnow;
        at++;

        charnow = (char)getchar_polling();
    }
    putchar('\n');
    buf[at] = 0;
}