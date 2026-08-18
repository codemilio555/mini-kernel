#include "kernel-files/malloc.h"
#include "kernel-files/stdint.h"
#include "kernel-files/print.h"
#include "kernel-files/stdkernel.h"
//void main(void) __attribute__((executable, visibility("default")));



void main(){
	//My kernel!!!
	init_malloc();

	print("Hallo Welt\n");

	print("How are you\n");
	print("\nMy kernel");
	char *text=malloc(50);

	strcpy(text,"\nHallo Welt, Malloc!");
	
	print(text);
	//set_cursor(5);
	while(1){}
}


