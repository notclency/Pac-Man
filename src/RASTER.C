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
			for(i = x1; i > y2; i--)
			{
				*(base + y1 * 80 + x1) = 0xff;
				y2 --;
			}
		}
		
	}
}
