#ifndef RASTER_H
#define RASTER_H

#include "TYPES.H"

/* check if plot is in bounds */
int in_bounds(int x, int y);


/* plot line methods */
void plot_pixel(char *base, int x, int y, int color);
void plot_vertical_line(char *base, int x1, int y1, int length, int color);
void plot_horizontal_line(char *base, int x1, int y1, int length, int color);

/* plot bitmap methods */
void plot_bitmap_8(UINT8 *base,int x, int y, const UINT8 *bitmap, unsigned int height);
void plot_bitmap_16(UINT16 *base,int x, int y, const UINT16 *bitmap, unsigned int height);
void plot_bitmap_32(UINT32 *base,int x, int y, const UINT32 *bitmap, unsigned int height);

/* draw shape methods */
void plot_rectangle(char *base, int x1, int y1, int width, int height, int color);
void plot_square(char *base, int x1, int y1, int size, int color);
void clear_pixel(char *base, int x, int y);

/* clear screen region / plots */
void clear_screen(char *base);
void clear_region_16(UINT16 *base, int x, int y);

/* print methods */
void print_char_8(UINT8 *base, int x, int y, char c);
void print_string_8(UINT8 *base, int x, int y, char *s);

void print_num(UINT8 *base, int x, int y, UINT16 num);

void plot_screen(UINT32 *base, UINT32 *bitmap);
void plot_map(UINT32 *base, UINT32 *map);

#endif
