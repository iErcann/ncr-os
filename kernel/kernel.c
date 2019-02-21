#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
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

#include "utils.c"
#include "io.c"

#include "vga.c"


#include "printf.c"
#include "keyboard.c"
 
 
 
void kernel_main(void) {
	/* Initialize terminal interface */
	terminal_initialize();
  
  	
	for (size_t e = 0; e < 7; e++) { 
		for (size_t i = 0; i < VGA_WIDTH; i++) {
			terminal_writestring(" ", 0, VGA_COLOR_LIGHT_GREY,VGA_COLOR_DARK_GREY);	
		}
	}

	terminal_column=0;
	terminal_row=0;
 
 
	char *buf[] = {"##    ##  ######  ########     #######   ######  \n",
	 			   "###   ## ##    ## ##     ##   ##     ## ##    ## \n",
	 			   "####  ## ##       ##     ##   ##     ## ##		 \n",
				   "## ## ## ##       ########    ##     ##  ######  \n",
	 			   "##  #### ##       ##   ##     ##     ##       ## \n",
	 			   "##   ### ##    ## ##    ##    ##     ## ##    ## \n"
	  			   "##    ##  ######  ##     ##    #######   ######  \n"
	  };

 
	terminal_row = 0;
	for (size_t i = 0; i < 6; i++) {
	 	terminal_writestring(buf[i], 0, VGA_COLOR_LIGHT_GREY, VGA_COLOR_DARK_GREY);	
	}   
	
 	int offsetX = 0;
	for (;;) {
		terminal_initialize();
		
		size_t WIDTH = 30;
		size_t HEIGHT = 15;
		
		for (size_t x = 0; x < WIDTH; x++){
			terminal_writestring_at(" ", 0, VGA_COLOR_WHITE, VGA_COLOR_LIGHT_BLUE, x+offsetX, 0);
			terminal_writestring_at(" ", 0, VGA_COLOR_WHITE, VGA_COLOR_LIGHT_BLUE,  x+offsetX, HEIGHT);
		}
		for (size_t y = 0; y < HEIGHT; y++){
			terminal_writestring_at(" ", 0, VGA_COLOR_WHITE, VGA_COLOR_LIGHT_BLUE, 0+offsetX, y);
			terminal_writestring_at(" ", 0, VGA_COLOR_WHITE, VGA_COLOR_LIGHT_BLUE, WIDTH+offsetX, y);
		}
		
		terminal_writestring_at("Basic Window", 0, VGA_COLOR_WHITE, VGA_COLOR_LIGHT_BLUE, 0+offsetX, 0);
		terminal_writestring_at("x", 0, VGA_COLOR_RED, VGA_COLOR_LIGHT_BLUE, WIDTH+offsetX, 0);
		
		terminal_writestring_at("Hey. This is a window", 0, VGA_COLOR_WHITE, VGA_COLOR_DARK_GREY, 1+offsetX, 1);
		terminal_writestring_at("Or is it ?", 0, VGA_COLOR_WHITE, VGA_COLOR_DARK_GREY, 1+offsetX, 2);
		terminal_writestring_at("I don't know.", 0, VGA_COLOR_WHITE, VGA_COLOR_DARK_GREY, 1+offsetX, 3);

		offsetX++;
		delay(10000);

}	
	  k_initialize(); 
 
 
 
 
}

