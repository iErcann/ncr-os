 

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
 
void kernel_main(void) 
{

	for (;;) {  
	/* Initialize terminal interface */
	terminal_initialize();

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 80; j++) {
			terminal_writestring(" ", 0, 0, 	VGA_COLOR_LIGHT_BLUE);
		}
	}
	terminal_column = 0;
	terminal_row=0;
	char *buf[] = {"##    ##  ######  ########     #######   ######  \n",
				   "###   ## ##    ## ##     ##   ##     ## ##    ##\n",
				   "####  ## ##       ##     ##   ##     ## ##\n",
				   "## ## ## ##       ########    ##     ##  ######  \n",
				   "##  #### ##       ##   ##     ##     ##       ##\n",
				   "##   ### ##    ## ##    ##    ##     ## ##    ## \n"
				   "##    ##  ######  ##     ##    #######   ###### \n"
				};
 
 	for (size_t i = 0; i < 6; i++)
		terminal_writestring(buf[i], 10, VGA_COLOR_BLACK, VGA_COLOR_LIGHT_BLUE);
 
   


	/* Newline support is left as an exercise. */
	printf("Hey, print function is working. :)\nReturn in line too.");
	terminal_writestring("\nThis one is with a ", 500, VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	terminal_writestring("delay.", 2500, VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK);
 	 	


    
 	char* test = "Davis style------->";
	// terminal_column = 0;
	// terminal_row = 0;
	


   	for (size_t i = 0; i < 100; i++) {  
  //		terminal_initialize();
   		terminal_column++;

 		for (unsigned int c = 0; c < strlen(test); c++) {  
 			if (test[c]=='\n'){
 				terminal_row++;
 		}
 			terminal_putentryat(test[c], VGA_COLOR_RED, c+terminal_column, terminal_row);
 		}
		
 		terminal_putentryat(' ', terminal_color, terminal_column-1, terminal_row);
 		delay(300);

 	}

 	printf(" Some not random numbers.");
 	for (size_t i = 0; i < 10; i++) {
 		terminal_putentryat(rand()%10+'0', i, terminal_column++, terminal_row);
 		delay(1000);
 	}

 	for (size_t i = 0; i < 500; i++) {
		terminal_writestring(" ", rand()%10*10, VGA_COLOR_WHITE, i);
 	}

 	}

}