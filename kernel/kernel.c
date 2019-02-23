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
	
 
	k_initialize(); 
	terminal_initialize();
		delay(10000);
for (int i = 1; i < 6; i++) {
	size_t w= 40;
	size_t h= i*5;
	int offsetX = (rand()%10)*8;
	int offsetY = (rand()%10);
	
	for (size_t x=0;x<w;x++){
		terminal_writestring_at(" ", 0,  VGA_COLOR_LIGHT_BLUE,   VGA_COLOR_LIGHT_BLUE, offsetX+x, offsetY+0);	
		for (size_t y=1;y<h;y++){
			terminal_writestring_at(" ", 0,   VGA_COLOR_WHITE,  VGA_COLOR_BLACK, offsetX+x, offsetY+y);	
		}
	}
	terminal_writestring_at("anon@anon:", 255,  VGA_COLOR_BLUE,   VGA_COLOR_LIGHT_BLUE, offsetX+0, offsetY+0);	
	terminal_column=offsetX;
	terminal_row=offsetY+1;
	terminal_output_prompt();
	delay(233);
}
	while (1){
		k_printKeyAt(terminal_column, terminal_row);
 	}
 
 
}

