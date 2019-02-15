#!/bin/bash

/home/iercan/Documents/i686/bin/i686-elf-as boot.s -o boot.o

/home/iercan/Documents/i686/bin/i686-elf-gcc -c kernel/kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -pedantic

/home/iercan/Documents/i686/bin/i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc


qemu-system-i386 -kernel myos.bin

