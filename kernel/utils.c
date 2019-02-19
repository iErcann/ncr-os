/*
 * utils.c
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

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}


size_t uint8_tlen(uint8_t str[]) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

int getIndex(char data,  uint8_t arr[]){
	for (size_t i = 0; i < uint8_tlen(arr); i++){
		if (data == arr[i]) return i;
	}
	return -1;
}
 
