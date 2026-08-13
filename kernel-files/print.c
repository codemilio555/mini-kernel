#include "print.h"

char *video =(char*)0xb4000;

int write_pos=0;

void print(char *value){

    for (int i = 0; value[i] != 0; i++)
    {
        if (value[i] == '\n')
        {
            //*2 beacause we have color and char
            write_pos=(write_pos-((SCREEN_WIDTH*2)%80))+(SCREEN_WIDTH*2);
        }
	//go back  to start of line
	if(value[i]=='\r'){
		write_pos = write_pos-(SCREEN_WIDTH*2)%80;
	}
        // printing char
        video[write_pos] = value[i];
        write_pos++;
        // printing color(white/lightgrey)
        video[write_pos] = 0x07;
        write_pos++;
    }
}
