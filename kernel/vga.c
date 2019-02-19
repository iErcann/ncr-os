

 /* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
 
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 	
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}


static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outportb(0x3D4, 0x0A);
	outportb(0x3D5, (inportb(0x3D5) & 0xC0) | cursor_start);
 
	outportb(0x3D4, 0x0B);
	outportb(0x3D5, (inportb(0x3D5) & 0xE0) | cursor_end);
}

void update_cursor(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;
 
	outportb(0x3D4, 0x0F);
	outportb(0x3D5, (uint8_t) (pos & 0xFF));
	outportb(0x3D4, 0x0E);
	outportb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}
void terminal_updateCursor(){
	update_cursor(terminal_column, terminal_row);
}
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	enable_cursor(0, 15);
	
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

void terminal_scrolldown() {
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0;  x < VGA_WIDTH; x++) {
			const size_t index = (y) * VGA_WIDTH + x;
			terminal_buffer[index] = terminal_buffer[ (y+1) * VGA_WIDTH + x ]; 
		}
	}
}
void terminal_scrollright() {
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0;  x < VGA_WIDTH; x++) {
			const size_t index = (y) * VGA_WIDTH + x;
			terminal_buffer[index] = terminal_buffer[ (y) * VGA_WIDTH + (x+1) ]; 
		}
	}
}
void terminal_scrolleft() {
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0;  x < VGA_WIDTH; x++) {
			const size_t index = (y) * VGA_WIDTH + x;
			terminal_buffer[index] = terminal_buffer[ (y) * VGA_WIDTH + (x-1) ]; 
		}
	}
}

 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	update_cursor(x+1, y);
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

 	
void terminal_putchar(char c) {
	if (c!='\n')
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	
	if (++terminal_column == VGA_WIDTH || c == '\n') {
		terminal_column = 0;
		if (++terminal_row >= VGA_HEIGHT) {
			terminal_scrolldown();
			terminal_row--;
			//terminal_row = 0;
		}
	}

}
 
void terminal_write(const char* data, size_t size, int delayTime) 
{
	for (size_t i = 0; i < size; i++) {
		terminal_putchar(data[i]);
		delay(delayTime);
	}
}

void terminal_writestring(const char* data, int delayTime, enum vga_color fg, enum vga_color bg) {
	uint8_t old_terminal_color = terminal_color;
	terminal_color = vga_entry_color(fg, bg);
	terminal_write(data, strlen(data), delayTime);
	terminal_color = old_terminal_color;

}

 
