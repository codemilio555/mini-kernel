#include "kernel-files/print.h"

void main(void) __attribute__((executable, visibility("default")));

volatile char* const vga = (char*)0xB8000;

void main(){
	//My kernel!!!

	print("Hallo Welt\n");
	print("How are you");
	while(1){}
}


