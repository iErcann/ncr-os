/*
 * printf.c
 * 
 * Copyright 2019 iercan <iercan@iercan>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


 

void printf(const char* data) {
	terminal_writestring(data, 1, VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

void printfg(const char* data,  enum vga_color fg) {
	terminal_writestring(data, 1, fg, VGA_COLOR_BLACK);
}

void printfc(const char data) {
	terminal_putchar(data);
}





