#include "stdkernel.h"

void outb(unsigned short port, unsigned char val){
	__asm__ __volatile__ ("outb %b0, %w1" :: "a"(val), "Nd"(port));
}
	
unsigned char inb(unsigned short port){
	unsigned char in;
	__asm__ __volatile__ ("inb %w1, %b0" : "=a"(in) : "Nd"(port));
	return in;
}
void strcpy(char *destSi, const char *srcSi){

	unsigned char* dest=(unsigned char*)destSi;
	unsigned char* src=(unsigned char*)srcSi;
	int i =0;
	for(;src[i]!=0;i++){
		dest[i]=src[i];
	}
	dest[i]=0;
}
void itoa(int n, char *str){
	int isn = 0;
	int i=0;
	if(n<0){
		isn=1;
		n=-n;
	}

	while(n>0){
		int num = n %10;
		str[i++]=num+'0';
		n=n/10;
	}

	if(isn==1){
		str[i]='-';
		i++;
	}

	str[i]=0;

	int at = 0;
	int end = i-1;
	while(at<end){
		char temp = str[at];
		str[at] = str[end];
		str[end]=temp;
		at++;
		end--;
	}



}
