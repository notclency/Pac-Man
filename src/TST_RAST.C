/*
	File Name: TST_RAST.C

	Purpose: This file is used to build the bitmaps pixels, and calls 
	the functions that will display them on the screen.

	Authors: Glenn and Clency

*/

#include <osbind.h>
#include <stdio.h>
#include "RASTER.H"
#include "font.h"
#include "splash.h"

UINT16 paul16[16] = {
	0xFFFF, 0xFC3F, 0xF00F, 0xE007, 
	0xC003, 0xC003, 0xF801, 0xFC01, 
	0xFE01, 0xFC01, 0xF803, 0xC003, 
	0xE007, 0xF00F, 0xFC3F, 0xFFFF
 
};

UINT16 pacman[16] = {
		0xFFFF, 0xFC3F, 0xF00F, 0xE007, 
		0xC003, 0xC003, 0xF801, 0xFC01, 
		0xFE01, 0xFC01, 0xF803, 0xC003, 
		0xE007, 0xF00F, 0xFC3F, 0xFFFF 
};

void display_splash_screen(char *base);

int main()
{
	char *base = Physbase();
	UINT8 *base8 = (UINT8 *)Physbase();
	UINT32 *base32 = (UINT32 *)Physbase();
	UINT16 *base16 = (UINT16 *)Physbase();
	
	display_splash_screen(base);
	
	return 0;
}

void display_splash_screen(char *base)
{
	/*clear_screen(base);*/
	plot_screen((UINT32 *)base, (UINT32 *)splash_screen);

	plot_pixel(base, 0, 0, black);

	print_string_8(base, 288, 220, "1 PLAYER");
	print_string_8(base, 288, 250, "2 PLAYERS");
	print_string_8(base, 212, 325, "MADE BY CLENCY & GLENN - 2023");
}
