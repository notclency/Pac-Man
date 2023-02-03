#include "raster.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

void plot_pixel(char *base, int x, int y)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		*(base + y * 80 + x) = 0xff;
	}
}

void plot_vertical_line(char *base, int x1, int y1, int y2)
{
	int i;

	if (x1 >= 0 && x1 < SCREEN_WIDTH && y1 >= 0 && y1 < SCREEN_HEIGHT && y2 >= 0 && y2 < SCREEN_HEIGHT)
	{
		if (y1 >= y2)
		{
			for (i = 0; i > y2; i--)
			{
				*(base + y1 * 80 + x1) = 0xff;
				y1--;
			}
		}
		else
		{
			for (i = 0; i < y2; i++)
			{
				*(base + y1 * 80 + x1) = 0xff;
				y1++;
			}
		}
	}else
	{
		return;
	}
}

void plot_horizontal_line(char *base, int x1, int x2, int y1)
{
	int i;

	if (x1 >= 0 && x1 < SCREEN_WIDTH && x2 >= 0 && x2 < SCREEN_WIDTH && y1 >= 0 && y1 < SCREEN_HEIGHT)
	{
		if (x1 >= x2)
		{
			for (i = 0; i > x2; i--)
			{
				*(base + y1 * 80 + x1) = 0xff;
				x1--;
			}
		}
		else
		{
			for (i = 0; i < x2; i++)
			{
				*(base + y1 * 80 + x1) = 0xff;
				x1++;
			}
		}
	}
	else
	{
		return;
	}
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
			*(base + y * 80 + x) = bitmap[i];
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
			*(base + y * 80 + x) = bitmap[i];
			y++;
		}
	}
}

void clear_screen(char *base)
{
	int x;

	for (x = 0; x < SCREEN_WIDTH * SCREEN_HEIGHT; x++)
	{
		*(base + x) = 0x00;
	}
}

void clear_region(char *base, int x1, int y1, int x2, int y2)
{
	int x, y;

	if (x1 >= 0 && x1 < SCREEN_WIDTH && x2 >= 0 && x2 < SCREEN_WIDTH && y1 >= 0 && y1 < SCREEN_HEIGHT && y2 >= 0 && y2 < SCREEN_HEIGHT)
	{
		for (y = y1; y < y2; y++)
		{
			for (x = x1; x < x2; x++)
			{
				*(base + x) = 0x00;
			}
		}
	}
}
