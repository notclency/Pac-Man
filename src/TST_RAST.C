#include <osbind.h>
#include <stdio.h>
#include "RASTER.H"
#include "font.h"

UINT16 paul16[16] = {
	0xFFFF, 0xFC3F, 0xF00F, 0xE007, 
	0xC003, 0xC003, 0xF801, 0xFC01, 
	0xFE01, 0xFC01, 0xF803, 0xC003, 
	0xE007, 0xF00F, 0xFC3F, 0xFFFF
 
};

UINT32 paul32[32] = {
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFF007FF, 
	0xFFC7F1FF, 0xFF9FFCFF, 0xFF3FFE7F, 0xFE7FFF7F, 
	0xFCFFFF3F, 0xFDFFFFBF, 0xF81C0F9F, 0xF3E9F7DF, 
	0xEFEBF00F, 0xEFE3F66F, 0xEFEBF5EF, 0xEFEBE5AF, 
	0xF71C0F4F, 0xF07FFFDF, 0xFB7EFE1F, 0xFB60FEFF, 
	0xF70FFEFF, 0xF7FFFEFF, 0xF7FEFCFF, 0xF6FDF9FF, 
	0xFB03FBFF, 0xFBFFF3FF, 0xF8FFE7FF, 0xFE1FCFFF, 
	0xFFC01FFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF 

 
};

UINT16 pacman[16] = {
		0xFFFF, 0xFC3F, 0xF00F, 0xE007, 
		0xC003, 0xC003, 0xF801, 0xFC01, 
		0xFE01, 0xFC01, 0xF803, 0xC003, 
		0xE007, 0xF00F, 0xFC3F, 0xFFFF 
};

UINT16 invader_bitmap[16] = 
{
    0x0000,
    0x0810,
    0x0810,
    0x0420,
    0x0240,
    0x1FF8,
    0x2004,
    0x4662,
    0x4002,
    0x43C2,
    0x2424,
    0x1008,
    0x0FF0,
    /*last 3 elements*/
    0x0240,
    0x0E70,
    0x0000
};

int main()
{
	int i;
	int j;

	void *base = Physbase();

	UINT8 *base8 = (UINT8 *)Physbase();
	UINT32 *base32 = (UINT32 *)Physbase();
	UINT16 *base16 = (UINT16 *)Physbase();
	
	clear_screen(base);

	plot_bitmap_16(base16, 2, 100, pacman, 16);

	print_string(base, 100, 200, "Clency");

	print_char(base,100,250,'P');
	print_char(base,108,250,'A');
	print_char(base,116,250,'C');
	print_char(base,124,250,'-');
	print_char(base,132,250,'M');
	print_char(base,140,250,'A');
	print_char(base,148,250,'N');
	
	print_string(base, 100, 300, "GLENN");

	plot_pixel(base, 10, 12);
	
	return 0;
}
