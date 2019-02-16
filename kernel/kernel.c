#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 
#include "rand.c"

void delay(int t) {
	for (int i = 0; i < t; i++) {
		for (int j = 0; j < 50000; j++) {
			__asm__("NOP");
		}
	}
}

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

#include "vga.c"

 
 
void printf(const char* data) {
	terminal_writestring(data, 1, VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

void kernel_main(void) {
	/* Initialize terminal interface */
	terminal_initialize();
  
	
	terminal_column = 0;
	terminal_row = 0;


	char *buf[] = {"##    ##  ######  ########     #######   ######  \n",
				   "###   ## ##    ## ##     ##   ##     ## ##    ## \n",
				   "####  ## ##       ##     ##   ##     ## ##		 \n",
				   "## ## ## ##       ########    ##     ##  ######  \n",
				   "##  #### ##       ##   ##     ##     ##       ## \n",
				   "##   ### ##    ## ##    ##    ##     ## ##    ## \n"
				   "##    ##  ######  ##     ##    #######   ######  \n"
	};

	terminal_column=0;
	terminal_row=0;

	for (size_t i = 0; i < 6; i++) {
		terminal_writestring(buf[i], 10, VGA_COLOR_WHITE, VGA_COLOR_LIGHT_BLUE);	
	}	
	printf("qsd aze qsd wxc qsd aze qsd wxc qsd aze qsd wxc qsd aze qsd wxc qsd aze qsd");

	for (;;){
		terminal_initialize();
		for (size_t i = 0; i < VGA_WIDTH; i++){
			terminal_putentryat('e', VGA_COLOR_WHITE, i, 0);
			//terminal_writestring(" ", 0, VGA_COLOR_RED,   VGA_COLOR_RED);
			//terminal_writestring(" ", 0, VGA_COLOR_RED,   VGA_COLOR_RED);
		}
		delay(100);
	}
}

