//#include "print.c"

//The screen width usually 80
#define SCREEN_WIDTH 80

//The screen height, I don't know it,,,
#define SCREEN_HEIGHT 40

void set_cursor(int pos);
void print(char *value);
void putchar(char char_print);
void printlen(char *toPrint, unsigned int len);