all: iso/

kernel.o: kernel.c
	gcc -m32 -ffreestanding -fno-pie -fno-pic -fno-stack-protector -fno-asynchronous-unwind-tables -c kernel.c -o kernel.o
boot.o: boot.asm
	nasm -f elf32 boot.asm -o boot.o

kernel.bin: kernel.o boot.o
	ld -m elf_i386 -T linker.ld -o kernel.bin boot.o kernel.o
iso/: kernel.bin
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/
	cp grub.cfg iso/boot/grub/
	grub-mkrescue -o kernel.iso iso

run: kernel.iso
	qemu-system-i386 -cdrom kernel.iso

clean:
	rm *.o kernel.bin
	rm -r iso
