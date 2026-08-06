//#include "print.c"

//The screen width usually 80
#define SCREEN_WIDTH 80

//The screen height, I don't know it,,,
#define SCREEN_HEIGHT 40

char *video=(char*)0xb4000;

int write_pos = 0;

void print(char *value);