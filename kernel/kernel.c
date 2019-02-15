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
	/* Initialize terminal interface */
	terminal_initialize();

	/* Newline support is left as an exercise. */
	printf("Hey, print function is working. \n Return in line");
	terminal_writestring("\nThis one is with \n a delay. ", 1000, VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_BLACK);

	for (size_t x = 0; x < 20; x++) {
		//terminal_writestring("Welcome to ncr OS\n", 1, x, VGA_COLOR_BLACK);
    	//terminal_putchar(rand()%10+'0');
	}
    
 // 	char* test = "Davis style->";
	// terminal_column = 0;
	// terminal_row = 0;
	


// 	for (;;) {  
// //		terminal_initialize();
// 		terminal_column++;

// 		for (unsigned int c = 0; c < strlen(test); c++) {  
// 			if (test[c]=='\n'){
// 				terminal_row++;
// 			}
// 			terminal_putentryat(rand()%10+'0', terminal_color, c+terminal_column, terminal_row);
// 		}
		
// 		terminal_putentryat(' ', terminal_color, terminal_column-1, terminal_row);
// 		delay(500);
// 	}
}