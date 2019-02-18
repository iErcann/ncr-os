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
#include "io.c"


 
 
void printf(const char* data) {
	terminal_writestring(data, 1, VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

void kernel_main(void) {
	/* Initialize terminal interface */
	terminal_initialize();
  
  	
	for (size_t e = 0; e < 7; e++) { 
		for (size_t i = 0; i < VGA_WIDTH; i++) {
			terminal_writestring(" ", 0, VGA_COLOR_RED,VGA_COLOR_LIGHT_RED);	
		}
	}

	terminal_column=0;
	terminal_row=0;
	
/*
	char *buf[] = {"##    ##  ######  ########     #######   ######  \n",
	 			   "###   ## ##    ## ##     ##   ##     ## ##    ## \n",
	 			   "####  ## ##       ##     ##   ##     ## ##		 \n",
				   "## ## ## ##       ########    ##     ##  ######  \n",
	 			   "##  #### ##       ##   ##     ##     ##       ## \n",
	 			   "##   ### ##    ## ##    ##    ##     ## ##    ## \n"
	  			   "##    ##  ######  ##     ##    #######   ######  \n"
	  };

 

	for (size_t i = 0; i < 6; i++) {
	 	terminal_writestring(buf[i], 0, VGA_COLOR_RED, VGA_COLOR_LIGHT_RED);	
	}  */
	
	uint8_t lastret = 0x00;
	
	for (;;)	{
		
		// Azerty keyboard.
		uint8_t ret = inportb(0x60);

 
		 if (lastret != ret) {
			if (ret == 0x14){
				printf("t");
			} else if (ret == 0x10){
				printf("a");
			} else if (ret == 0x11) {
				printf("z");
			} else if (ret == 0x12) {
				printf("e");
			} else if (ret == 0x13) {
				printf("r");
			} else if (ret == 0x14) {
				printf("t");
			} else if (ret == 0x15) {
				printf("y");
			} else if (ret == 0x16) {
				printf("u");
			} else if (ret == 0x17) {
				printf("i");
			} else if (ret == 0x18) {
				printf("o");
			} else if (ret == 0x19) {
				printf("p");
			} 
			
			else if (ret == 0x1E) {
				printf("q");
			} else if (ret == 0x1F) {
				printf("s");
			} else if (ret == 0x20) {
				printf("d");
			} else if (ret == 0x21) {
				printf("f");
				terminal_scrollright();

			} else if (ret == 0x22) {
				printf("g");
			} else if (ret == 0x23) {
				printf("h");
			} else if (ret == 0x24) {
				printf("j");
			} else if (ret == 0x25) {
				printf("k");
			} else if (ret == 0x26) {
				printf("l");
			} else if (ret == 0x27) {
				printf("m");
			}
			
			else if (ret == 0x2C) {
				printf("w");
			} else if (ret == 0x2D) {
				printf("x");
			} else if (ret == 0x2E) {
				printf("c");
			} else if (ret == 0x2F) {
				printf("v");
			} else if (ret == 0x30) {
				printf("b");
			} else if (ret == 0x31) {
				printf("n");
			} else if (ret == 0x1C) { // enter
				printf("\n");
			} else if (ret == 0x39) {
				printf(" ");
			} else if (ret == 0x0E) {
				terminal_column--;
				printf(" ");
				terminal_column-=2;
				printf(" ");
			} else if (ret == 0x0C) {
				terminal_scrollright();
			}
		}
		
		lastret = ret;

 
 
	}
}

