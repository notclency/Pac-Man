#include "include\SPRITES.H"

const UINT16 cherry_sprite[16] = {
	0xFFFF, 0xFFFF, 0xFFF3, 0xFFF3,
	0xFFC3, 0xFF2F, 0xE0EF, 0xDF5F,
	0xBF3F, 0xBC03, 0xBD7D, 0xBD7D,
	0xC17D, 0xFF7D, 0xFF83, 0xFFFF};

const UINT16 pacman_closed[16] = {
	0xFFFF, 0xF83F, 0xE00F, 0xC007,
	0xC007, 0x8003, 0x8003, 0x8003,
	0x8003, 0x8003, 0xC007, 0xC007,
	0xE00F, 0xF83F, 0xFFFF, 0xFFFF
};

const UINT16 pacman_left[16] = {
	0xFFFF, 0xF83F, 0xE00F, 0xC007,
	0xC007, 0xF003, 0xFE03, 0xFFC3,
	0xFE03, 0xF003, 0xC007, 0xC007,
	0xE00F, 0xF83F, 0xFFFF, 0xFFFF
};

const UINT16 pacman_left_open[16] = {
	0xFFFF, 0xF83F, 0xF80F, 0xFC07,
	0xFE07, 0xFF03, 0xFF83, 0xFFC3,
	0xFF83, 0xFF03, 0xFE07, 0xFC07,
	0xF80F, 0xF83F, 0xFFFF, 0xFFFF
};

const UINT16 pacman_right[16] = {
	0xFFFF, 0xFC1F, 0xF007, 0xE003,
	0xE003, 0xC00F, 0xC07F, 0xC3FF,
	0xC07F, 0xC00F, 0xE003, 0xE003,
	0xF007, 0xFC1F, 0xFFFF, 0xFFFF};

const UINT16 pacman_right_open[16] = {
	0xFFFF, 0xFC1F, 0xF01F, 0xE03F,
	0xE07F, 0xC0FF, 0xC1FF, 0xC3FF,
	0xC1FF, 0xC0FF, 0xE07F, 0xE03F,
	0xF01F, 0xFC1F, 0xFFFF, 0xFFFF
};

const UINT16 pacman_up[16] = {
	0xFFFF, 0xFFFF, 0xF3E7, 0xE3E3,
	0xE1C3, 0xC1C1, 0xC1C1, 0xC081,
	0xC081, 0xC081, 0xE003, 0xE003,
	0xF007, 0xFC1F, 0xFFFF, 0xFFFF
};

const UINT16 pacman_up_open[16] = {
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
	0xFFFF, 0x9FF3, 0x8FE3, 0x87C3,
	0x8383, 0x8103, 0xC007, 0xC007,
	0xE00F, 0xF83F, 0xFFFF, 0xFFFF
};

const UINT16 pacman_down[16] = {
	0xFFFF, 0xFFFF, 0xFC1F, 0xF007,
	0xE003, 0xE003, 0xC081, 0xC081,
	0xC081, 0xC1C1, 0xC1C1, 0xE1C3,
	0xE3E3, 0xF3E7, 0xFFFF, 0xFFFF
};

const UINT16 pacman_down_open[16] = {
	0xFFFF, 0xF83F, 0xE00F, 0xC007,
	0xC007, 0x8103, 0x8383, 0x87C3,
	0x8FE3, 0x9FF3, 0xFFFF, 0xFFFF,
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
};

const UINT16 emp[16] = {
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
};

const UINT16 ghost_sprite[16] = {
	0xFFFF, 0xFC3F, 0xF3CF, 0xEFF7,
	0xDFFB, 0xDCCB, 0xDAAB, 0xBAAD,
	0xBCCD, 0xBFFD, 0xBFFD, 0xBFFD,
	0xBBDD, 0xB5AD, 0xCE73, 0xFFFF
};

const UINT16 ghost_scatter_sprite[16] = {
	0xFFFF, 0xFC3F, 0xF3CF, 0xEFF7,
	0xDFFB, 0xD99B, 0xD99B, 0xBFFD,
	0xBFFD, 0xBFFD, 0xB99D, 0xB66D,
	0xBFFD, 0xBBDD, 0xB5AD, 0xCE73
};

const UINT16 snack_sprite[16] = {
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
	0xFFFF, 0xFFFF, 0xFC3F, 0xFC3F,
	0xFC3F, 0xFC3F, 0xFFFF, 0xFFFF,
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
};

const UINT16 glow_ball_sprite[16] = {
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
	0xFE7F, 0xF81F, 0xF81F, 0xF00F,
	0xF00F, 0xF81F, 0xF81F, 0xFE7F,
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
};

UINT16 mouse_bg_1[16];
UINT16 mouse_bg_2[16];

const UINT16 mouse_ptr[16] = {
	0x003F, 0x7C3F, 0x423F, 0x413F, 
	0x403F, 0x4007, 0x2007, 0x1007, 
	0x0007, 0x0007, 0xF807, 0xF803, 
	0xF801, 0xFFE0, 0xFFF0, 0xFFF8  
};
