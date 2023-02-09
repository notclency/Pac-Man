#include "RASTER.H"
#include "font.h"

#define SCREEN_WIDTH 640 /* 80 working in bytes */
#define SCREEN_HEIGHT 400

/*
plot_pixel
plot_vertical_line
plot_horizontal_line
plot_bitmap_8
plot_bitmap_16
plot_bitmap_32
plot_rectangle
plot_square
clear_pixel
clear_screen
clear_region
black_screen
black_region
shift_bitmap16
*/

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
void plot_pixel(char *base, int x, int y)
{
	*(base + y * 80 + (x >> 3)) |= 1 << 7 - (x & 7);
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
void plot_vertical_line(char *base, int x1, int y1, int y2)
{
	int i;

	if (x1 >= 0 && x1 < SCREEN_WIDTH && y1 >= 0 && y1 < SCREEN_HEIGHT && y2 >= 0 && y2 < SCREEN_HEIGHT)
	{
		for (i = y1; i <= y2; i++)
		{
			plot_pixel(base, x1, i);
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
void plot_horizontal_line(char *base, int x1, int y1, int x2)
{
	int i = (x2 - x1) / 8;

	if (x1 >= 0 && x1 < SCREEN_WIDTH && x2 >= 0 && x2 < SCREEN_WIDTH && y1 >= 0 && y1 < SCREEN_HEIGHT)
	{
		while (x1 % 8 != 0 && x1 <= x2)
		{
			plot_pixel(base, x1, y1);
			x1++;
		}
		while (i > 0)
		{
			*(base + y1 * 80 + (x1 >> 3)) = 0xff;
			x1 += 8;
			i--;
		}
		while (x1 <= x2)
		{
			plot_pixel(base, x1, y1);
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
void plot_rectangle(char *base, int x1, int y1, int x2, int y2)
{
	if (x1 >= 0 && x1 < SCREEN_WIDTH && x2 >= 0 && x2 < SCREEN_WIDTH && y1 >= 0 && y1 < SCREEN_HEIGHT && y2 >= 0 && y2 < SCREEN_HEIGHT)
	{
		plot_horizontal_line(base, x1, y1, x2);
		plot_horizontal_line(base, x1, y2, x2);
		plot_vertical_line(base, x1, y1, y2);
		plot_vertical_line(base, x2, y1, y2);
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
void plot_square(char *base, int x, int y, int size)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		plot_horizontal_line(base, x, y, x + size - 1);
		plot_vertical_line(base, x, y, y + size - 1);
		plot_vertical_line(base, x + size - 1, y, y + size - 1);
		plot_horizontal_line(base, x, y + size - 1, x + size - 1);
	}
	else
	{
		return;
	}
}

/*
	parameters:
		base: pointer to the base address of the screen

	description:
		clears the screen

	returns:
		none
*/
void clear_screen(char *base)
{
	int i;
	int j;

	for (i = 0; i < 80; i++)
	{
		for (j = 0; j < 400; j++)
		{
			clear_pixel(base, i, j);
		}
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
		*(base + y * 80 + x) = 0x00;
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
		clears a region of the screen

	returns:
		none
*/
void clear_region(char *base, int x1, int y1, int x2, int y2)
{
	int i;
	int j;

	if (x1 >= 0 && x1 < SCREEN_WIDTH && x2 >= 0 && x2 < SCREEN_WIDTH && y1 >= 0 && y1 < SCREEN_HEIGHT && y2 >= 0 && y2 < SCREEN_HEIGHT)
	{
		for (i = x1; i <= x2; i++)
		{
			for (j = y1; j <= y2; j++)
			{
				clear_pixel(base, i, j);
			}
		}
	}
}

void black_screen(char *base)
{
	int i;
	int j;

	for (i = 0; i < 80; i++)
	{
		for (j = 0; j < 400; j++)
		{
			plot_pixel(base, i, j);
		}
	}
}

void black_region(char *base, int x1, int y1, int x2, int y2)
{
	int i;
	int j;

	if (x1 >= 0 && x1 < SCREEN_WIDTH && x2 >= 0 && x2 < SCREEN_WIDTH && y1 >= 0 && y1 < SCREEN_HEIGHT && y2 >= 0 && y2 < SCREEN_HEIGHT)
	{
		for (i = x1; i <= x2; i++)
		{
			for (j = y1; j <= y2; j++)
			{
				plot_pixel(base, i, j);
			}
		}
	}
}

void print_char(char *base, int x, int y, char ch)
{
	int i = 0;
	/*
	 * start font from given char
	 */
	if (IS_PRINTABLE(ch))
	{
		UINT8 *char_hex = (UINT8 *) GLYPH_START(ch);
		for (i = 0; i < 8; i++, char_hex++)
		{
			*(base + (y + i) * 80 + (x >> 3)) = *char_hex;
		}
	}

}

void print_string(char *base, int x, int y, char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		print_char(base, x, y, str[i]);
		x += 8;
		i++;
	}
}
