all: iso/
ARCH := $(shell arch)


CC := gcc
LD := ld

mac: CC := i686-elf-gcc
mac: LD := i686-elf-ld




C_SOURCE := $(wildcard kernel-files/*.c)

CFLAGS := -nostdlib -m32 -O0 -ffreestanding -fno-pie -fno-pic -fno-stack-protector -fno-asynchronous-unwind-tables

OBJ := kernel.o boot.o $(C_SOURCE:.c=.o)

ifeq (,$(filter, aarch64, arm64,$(ARCH)))
	CC := i686-linux-gnu-gcc
	LD := i686-linux-gnu-ld
endif

mac: iso/
comp_lib: 
	@for file in kernel-files/*.c; do \
		$(CC) $(CFLAGS) -c "$$file" -o "$${file%.c}.o"; \
	done

kernel.o: kernel.c
	
		$(CC) $(CFLAGS) -c kernel.c -o kernel.o

boot.o: boot.asm
	nasm -f elf32 boot.asm -o boot.o

kernel.bin: kernel.o boot.o comp_lib
		$(LD) -nostdlib -m elf_i386 -s -T linker.ld -o kernel.bin $(OBJ)

iso/: kernel.bin
	mkdir -p iso/boot/grub
	mkdir -p iso/EFI/BOOT
	cp kernel.bin iso/boot/
	cp grub.cfg iso/boot/grub/

	grub-mkrescue -d /usr/lib/grub/i386-pc -o kernel.iso iso


	
clean:
	rm kernel-files/*.o
	rm *.o kernel.iso kernel.bin
	rm -r iso/
