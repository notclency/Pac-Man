#ifndef RASTER_H
#define RASTER_H

#include "types.h"

/* [TO DO] the functions below are examples. Replace them! */

void plot_pixel(char *base, int x, int y);

void plot_vertical_line(char *base, int x1, int y1, int y2);

void plot_horizontal_line(char *base, int x1, int x2, int y1);

void plot_bitmap_8(UINT8 *base,int x, int y, const UINT8 *bitmap, unsigned int height);

void plot_bitmap_16(UINT16 *base,int x, int y, const UINT16 *bitmap, unsigned int height);

void plot_bitmap_32(UINT32 *base,int x, int y, const UINT32 *bitmap, unsigned int height);


void clear_screen(char *base);

#endif
