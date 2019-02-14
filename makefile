AS = /home/iercan/Documents/i686/bin/i686-elf-as
CC = /home/iercan/Documents/i686/bin/i686-elf-gcc

main: kernel.c linker.ld boot.s
	$(AS) boot.s -o boot.o
	$(CC) -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -pedantic
	$(CC) -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
	qemu-system-i386 -kernel myos.bin

clean:
	rm ./*.o ./*.bin ./*.iso 