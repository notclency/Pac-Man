#include <osbind.h>
#include <stdio.h>
#include "RASTER.H"

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
	/*int i;
	/*int j;

	/*void *base = Physbase();

	/*clear_screen(base);

	/*plot_pixel(base, 79, 79);
	/*plot_pixel(base, 79, 330);

	/*plot_vertical_line(base, 75, 330, 79); /* x1,y2 < y1 */
	/*plot_vertical_line(base, 77, 79, 330); /* x1,y1 < y2 */

	/*plot_horizontal_line(base, 30, 79, 60); /* x2 > x1 */
	/*plot_horizontal_line(base, 60, 85, 30); /* x2 < x1 */

	/*clear_region(base, 30, 79, 60, 79);	 /* clear top line */
	/*clear_region(base, 77, 79, 77, 330); /* clear right line */

	/*plot_square(base, 1, 1, 50);
	/*plot_rectangle(base, 1, 100, 51, 200);*/

	void *base = Physbase();
	UINT32 *base32 = (UINT32 *)Physbase();
	UINT16 *base16 = (UINT16 *)Physbase();

	black_screen(base);

	plot_bitmap_16(base16, 20, 10, pacman, 16);
	plot_bitmap_16(base16, 10, 10, invader_bitmap, 16);
	plot_bitmap_16(base16, 11, 10, invader_bitmap, 16);


	return 0;
}
