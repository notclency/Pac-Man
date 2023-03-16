#include "INPUT.H"
#include <osbind.h>

UINT16 buffer_head = 0;
UINT16 buffer_tail = 0;
UINT8 IKBD_buffer[IKBD_BUFFER_SIZE];

volatile UINT8 const *IKBD_status = 0xFFFC00;
volatile UINT8 *IKBD_reader = 0xFFFC02;

volatile UINT8* const isrb_mfp_register = 0xFFFA11;


volatile UINT8 *ascii_table = (UINT8 *)0xFFFE829C;

int is_key_pressed()
{
    UINT32 old_ssp = Super(0);
    int key_pressed = *IKBD_status;
    Super(old_ssp);
    return key_pressed;
}

UINT32 read_from_ikbd_buffer()
{
    UINT32 key;
    UINT32 old_ssp = Super(0);

    /*
    if (buffer_head == IKBD_BUFFER_SIZE - 1)
        buffer_head = 0;
    
    *isrb_mfp_register &= MFB_BIT_6_MASK_OFF;

    key = IKBD_buffer[buffer_head];
    key = key << 16;
    key = key + *(ascii_table + IKBD_buffer[buffer_head++]);

    *isrb_mfp_register |= MFB_BIT_6_MASK_ON;
    */

    key = *IKBD_reader;
    key = key << 16;
    key = key + *(ascii_table + *IKBD_reader);
    

    Super(old_ssp);
    return key;
}

void clear_ikbd_buffer()
{
    buffer_head = 0;
    buffer_tail = 0;
}

UINT32 get_user_input(){
    return read_from_ikbd_buffer();
}