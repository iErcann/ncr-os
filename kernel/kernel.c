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

 

	for (size_t i = 0; i < 6; i++) {
	 	terminal_writestring(buf[i], 0, VGA_COLOR_LIGHT_GREY, VGA_COLOR_DARK_GREY);	
	}   
	
 
 

    k_initialize();
	 
}

