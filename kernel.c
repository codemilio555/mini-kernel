#include "kernel-files/malloc.h"
#include "kernel-files/stdint.h"
#include "kernel-files/print.h"
#include "kernel-files/stdkernel.h"
#include "kernel-files/input.h"
#include "kernel-files/tar.h"

struct __attribute__((packed)) GRUBboot
{

	uint32_t total_size;
	uint32_t reserved;

} GRUBmodule;
struct __attribute__((packed)) GRUBtag
{
	uint32_t type;
	uint32_t size;
};
struct __attribute__((packed)) GRUBmodule
{
	uint32_t type;
	uint32_t size;
	char *start;
};

// void main(void) __attribute__((executable, visibility("default")));
char *GRUB_get(uint32_t addrMultiboot)
{
	char input[100];
	struct GRUBboot *GRUB = (struct GRUBboot *)addrMultiboot;
	struct GRUBtag *tag = (struct GRUBtag *)((uint32_t)GRUB + 8);

	struct GRUBmodule *module;
	while (1)
	{
		if (tag->type == 0)
		{
			break;
		}
		if (tag->type == 3)
		{
			// module
			module = (struct GRUBmodule *)tag;
		}

		tag = (struct GRUBtag *)(((uint32_t)tag + tag->size + 7) & ~7);
	}
	return module->start;
}

void main(unsigned int magic, unsigned int addrMultiboot)
{

	char input[100];
	if (magic != 0x36d76289)
	{

		char buf[20];
		itoa((int)magic, buf);
		print("Error: Wrong magic: ");
		print(buf);
		print("\n Aborting...\n");
		return;
	}




	char *module = GRUB_get(addrMultiboot);


	char* test= get_from_tar_str(module, "programms/test_copy.o");
	print(test);
	
	int (*p)() = module;

	print("Command> ");

	read_input(input, 100);

	if (strcmp(input, "code") == 0)
	{
		int out = p();
		itoa(out, input);
		print(input);
		putchar('\n');
	}
	else
	{
		print("Command not found\n");
	}
}
