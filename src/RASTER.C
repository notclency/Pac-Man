/*
	File Name: RASTER.C

	Purpose: The purpose of this file is a library design of a
	pac-man game which develops low-level routines and other
	designs or drawings. We have created many plot functions
	that can plot bitmaps,pixel,shapes,clear/black screen.

	Authors: Glenn and Clency

*/
#include "RASTER.H"
#include "font.h"

/*
	index:

	plot pixel
	plot vertical line
	plot horizontal line
	plot bitmap
	plot rectangle
	plot square
	clear pixel
	clear screen
	print char
	print string
	plot screen
*/

/*
	parameters:
		x: x coordinate of the pixel
		y: y coordinate of the pixel

	description:
		checks if the pixel is in bounds

	returns:
		true if the pixel is in bounds
		false if the pixel is not in bounds
*/
int in_bounds(int x, int y)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
	parameters:
		base: pointer to the base address of the screen
		x: x coordinate of the pixel
		y: y coordinate of the pixel

	description:
		plots a pixel at the specified coordinates

	returns:
		none
*/
void plot_pixel(char *base, int x, int y, int color)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		*(base + y * 80 + (x >> 3)) = (*(base + y * 80 + (x >> 3)) & ~(0x80 >> (x & 0x7))) | ((color & 0x1) << (7 - (x & 0x7)));
	}

	return;
}

/*
	parameters:
		base: pointer to the base address of the screen
		x1: x coordinate of the first point
		y1: y coordinate of the first point
		y2: y coordinate of the second point / end coordinate of the line

	description:
		plots a vertical line from the first point to the second point

	returns:
		none
*/
void plot_vertical_line(char *base, int x1, int y1, int y2, int color)
{
	int i;

	if (x1 >= 0 && x1 < SCREEN_WIDTH && y1 >= 0 && y1 < SCREEN_HEIGHT && y2 >= 0 && y2 < SCREEN_HEIGHT)
	{
		for (i = y1; i <= y1 + y2; i++)
		{
			plot_pixel(base, x1, i, color);
		}
	}

	return;
}

/*
	parameters:
		base: pointer to the base address of the screen
		x1: x coordinate of the first point
		y1: y coordinate of the first point
		x2: x coordinate of the second point / end coordinate of the line

	description:
		plots a horizontal line from the first point to the second point

	returns:
		none
*/
void plot_horizontal_line(char *base, int x1, int y1, int length, int color)
{
	int x2 = x1 + length;

	int i = (x2 - x1) / 8;

	if (x1 >= 0 && x1 < SCREEN_WIDTH && x2 >= 0 && x2 < SCREEN_WIDTH && y1 >= 0 && y1 < SCREEN_HEIGHT)
	{
		while (x1 % 8 != 0 && x1 <= x2)
		{
			plot_pixel(base, x1, y1, color);
			x1++;
		}
		while (i > 0)
		{
			*(base + y1 * 80 + (x1 >> 3)) = color;
			x1 += 8;
			i--;
		}
		while (x1 <= x2)
		{
			plot_pixel(base, x1, y1, color);
			x1++;
		}
	}

	return;
}

void plot_bitmap_8(UINT8 *base, int x, int y, const UINT8 *bitmap, unsigned int height)
{
	int i;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		for (i = 0; i < height; i++)
		{
			*(base + y * 80 + x) = bitmap[i];
			y++;
		}
	}
}

void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height)
{
	int i;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		for (i = 0; i < height; i++)
		{
			*(base + y * 40 + x) = bitmap[i];
			y++;
		}
	}
}

void plot_bitmap_16_2(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height)
{
	int i;

	UINT16 mask_1 = 0xFFFF;
	UINT16 mask_2 = 0xFFFF;
	
	for (i = 0; i < height; i++)
	{
		*(base + (y * 40) + (x / 16)) = (bitmap[i] >> (x % 16));
		*(base + (y * 40) + (x / 16)) |= ((mask_1 >> (x % 16)) ^ 0xFFFF);


		if (x % 16 != 0) {
			*(base + (y * 40) + ((x / 16) + 1)) = bitmap[i] << (16 - (x % 16));
			*(base + (y * 40) + ((x / 16) + 1)) |= ((mask_2 << (16 - (x % 16))) ^ 0xFFFF);
		}

		y++;
	}
}

void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height)
{
	int i;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		for (i = 0; i < height; i++)
		{
			*(base + y * 20 + x) = bitmap[i];
			y++;
		}
	}
}

/*
	parameters:
		base: pointer to the base address of the screen
		x1: x coordinate of the first point
		y1: y coordinate of the first point
		x2: x coordinate of the second point
		y2: y coordinate of the second point

	description:
		plots a rectangle with the specified coordinates

	returns:
		none
*/
void plot_rectangle(char *base, int x1, int y1, int width, int height, int color)
{
	if (x1 >= 0 && x1 < SCREEN_WIDTH && y1 >= 0 && y1 < SCREEN_HEIGHT && x1 + width < SCREEN_WIDTH && y1 + height < SCREEN_HEIGHT)
	{
		plot_horizontal_line(base, x1, y1, width - 1, color);
		plot_horizontal_line(base, x1, y1 + height - 1, width - 1, color);
		plot_vertical_line(base, x1, y1, height - 1, color);
		plot_vertical_line(base, x1 + width - 1, y1, height - 1, color);
	}
	else
	{
		return;
	}
}

/*
	parameters:
		base: pointer to the base address of the screen
		x: x coordinate of the center of the square
		y: y coordinate of the center of the square
		size: size of the square

	description:
		plots a square with the specified size

	returns:
		none
*/
void plot_square(char *base, int x, int y, int size, int color)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		plot_horizontal_line(base, x, y, size, color);
		plot_vertical_line(base, x, y, size, color);
		plot_vertical_line(base, x + size, y, size, color);
		plot_horizontal_line(base, x, y + size, size, color);
	}
	else
	{
		return;
	}
}

/*
	parameters:
		base: pointer to the base address of the screen
		x: x coordinate of the pixel
		y: y coordinate of the pixel

	description:
		clears a pixel at the specified coordinates

	returns:
		none
*/
void clear_pixel(char *base, int x, int y)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		*(base + y * 80 + (x >> 3)) &= ~(0x80 >> (x % 8));
	}
	else
	{
		return;
	}
}

/*
	parameters:
		base: pointer to the base address of the screen
		x: x coordinate of the pixel
		y: y coordinate of the pixel

	description:
		plots a pixel at the specified coordinates

	returns:
		none
*/
void print_char_8(UINT8 *base, int x, int y, char ch)
{
	int i = 0;
	/*
	 * start font from given char
	 */
	if (IS_PRINTABLE(ch))
	{
		UINT8 *char_hex = (UINT8 *)GLYPH_START(ch);
		for (i = 0; i < 8; i++, char_hex++)
		{
			*(base + (y + i) * 80 + (x >> 3)) = *char_hex;
		}
	}
}

/*
	parameters:
		base: pointer to the base address of the screen
		x: x coordinate of the pixel
		y: y coordinate of the pixel

	description:
		plots a pixel at the specified coordinates

	returns:
		none
*/
void print_string_8(UINT8 *base, int x, int y, char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		print_char_8(base, x, y, str[i]);
		x += 8;
		i++;
	}
}

void print_num(UINT8 *base, int x, int y, UINT16 num)
{
	char a, b, c, d, e, f;

	f = (num % 10) + '0';
	num /= 10;

	e = (num % 10) + '0';
	num /= 10;

	d = (num % 10) + '0';
	num /= 10;

	c = (num % 10) + '0';
	num /= 10;

	b = (num % 10) + '0';
	num /= 10;

	a = (num % 10) + '0';

	print_char_8(base, x, y, a);
	print_char_8(base, x + 8, y, b);
	print_char_8(base, x + 16, y, c);
	print_char_8(base, x + 24, y, d);
	print_char_8(base, x + 32, y, e);
	print_char_8(base, x + 40, y, f);
}

void plot_map(UINT32 *base, UINT32 *map)
{
	int i;
	for (i = 0; i < MAP_BMP; i++)
		*(base + i) = map[i];
}

void plot_screen(UINT32 *base, UINT32 *bitmap)
{
	int i;
	for (i = 0; i < SCREEN_BMP; i++)
		*(base + i) = bitmap[i];
}

void clear_region_16(UINT16 *base, int x, int y)
{
	int i;
	for (i = 0; i < 16; i++)
		*(base + y + x + i) = 0;
}