#include "stdkernel.h"
#include "print.h"
#include "stdint.h"
static char buf[100];
char* itoa_smart(int n){
    itoa(n, buf);
    return buf;
}
char *get_from_tar_str(char *tar, char *filename)
{
    char *tarNow = tar;
    while (tarNow[0]!=0)
    {
        char *thisSize = ((int)tarNow + 124);
        int size = octal_to_dec(atoi(thisSize));

        print(tarNow);
        print(" len: ");
        print(itoa_smart(strlen(tarNow)));
        print("\nand\n");
        print(filename);
        print("\nstrcmp: ");
        print(itoa_smart(strcmp(tarNow, filename)));

        if (strcmp(tarNow, filename) == 0)
        {
            break;
        }
        int blocks = (size + 511) / 512;
        tarNow = tarNow + 512 + (blocks * 512);

    }
    if(tarNow[0]!=0){
        print("Error: In tar File ");
        print(filename);
        print(" not found\n");
        return NULL;
    }

    return tarNow + 512;
}