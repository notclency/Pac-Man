#ifndef INPUT_H
#define INPUT_H

#include "TYPES.H"
#define IKBD_BUFFER_SIZE 256

#define MFB_BIT_6_MASK_ON 0x40
#define MFB_BIT_6_MASK_OFF 0xbf

int is_key_pressed();

UINT32 read_from_ikbd_buffer();

void clear_ikbd_buffer();

UINT32 get_user_input();

#endif