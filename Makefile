all: iso/

ARCH := $(shell arch)

CC := gcc
LD := ld

C_SOURCE := $(wildcard kernel-files/*.c)

CFLAGS := -m32 -ffreestanding -fno-pie -fno-pic -fno-stack-protector -fno-asynchronous-unwind-tables

OBJ := boot.o $(C_SOURCE:.c=.o)

ifeq (,$(filter, aarch64, arm64,$(ARCH)))
	CC := i686-linux-gnu-gcc
	LD := i686-linux-gnu-ld
endif

comp_lib: 
	@for file in kernel-files/*.c; do \
		$(CC) $(CFLAGS) -c "$$file" -o "$${file%.c}.o"; \
	done

kernel.o: kernel.c
	
		$(CC) $(CFLAGS) -c kernel.c -o kernel.o

boot.o: boot.asm
	nasm -f elf32 boot.asm -o boot.o

kernel.bin: kernel.o boot.o comp_lib
		$(LD) -m elf_i386 -T linker.ld -o kernel.bin kernel.o $(OBJ)

iso/: kernel.bin
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/
	cp grub.cfg iso/boot/grub/
	grub-mkrescue -o kernel.iso iso
clean:
	rm *.o kernel.iso kernel.bin
	rm -r iso/
