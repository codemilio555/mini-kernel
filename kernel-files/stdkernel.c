#include "stdkernel.h"
#include "stdint.h"

void outb(unsigned short port, unsigned char val)
{
	__asm__ __volatile__("outb %b0, %w1" ::"a"(val), "Nd"(port));
}

unsigned char inb(unsigned short port)
{
	unsigned char in;
	__asm__ __volatile__("inb %w1, %b0" : "=a"(in) : "Nd"(port));
	return in;
}
int strlen(char *str)
{
	int i = 0;
	for (; str[i] != 0; i++)
	{
	}
	return i;
}

int strcmp(char *a, char *b)
{
	int at = 0;
	while (a[at] != 0 || b[at] != 0)
	{
		if (a[at] == b[at])
		{
			at++;
			continue;
		}
		return 1;
	}

	return 0;
}
int strncmp(const char *s1, const char *s2, unsigned int n)
{
	while (n && *s1 && (*s1 == *s2))
	{
		++s1;
		++s2;
		--n;
	}
	if (n == 0)
	{
		return 0;
	}
	else
	{
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
	}
}
void strcpy(char *destSi, const char *srcSi)
{

	unsigned char *dest = (unsigned char *)destSi;
	unsigned char *src = (unsigned char *)srcSi;
	int i = 0;
	for (; src[i] != 0; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = 0;
}
void itoa(int n, char *str)
{
	if(n==0){
		str="0";
	}
	int isn = 0;
	int i = 0;
	if (n < 0)
	{
		isn = 1;
		n = -n;
	}

	while (n > 0)
	{
		int num = n % 10;
		str[i++] = num + '0';
		n = n / 10;
	}

	if (isn == 1)
	{
		str[i] = '-';
		i++;
	}

	str[i] = 0;

	int at = 0;
	int end = i - 1;
	while (at < end)
	{
		char temp = str[at];
		str[at] = str[end];
		str[end] = temp;
		at++;
		end--;
	}
}

int atoi(char *str)
{
	int num = 0;
	while (*str != 0)
	{
		int actual_digit = *str - '0';

		num = num * 10;
		num += actual_digit;

		str++;
	}

	return num;
}

int octal_to_dec(int octal)
{
	int decimal = 0;
	int basis = 1;
	int tmp = octal;
	while (tmp > 0)
	{
		decimal += (tmp % 10) * basis;
		tmp = tmp / 10;
		basis = basis * 8;
	}

	return decimal;
}