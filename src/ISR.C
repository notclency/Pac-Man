/*
---------------------------------------------------------------------------------------------------
File Name: ISR.C
---------------------------------------------------------------------------------------------------
Purpose: This file contains the interrupt service routines for the game. It handles the keyboard
and mouse interrupts. It also contains the keyboard and mouse functions. This file also contains
the game timer and vbl request function which is used to syncronize the game.
---------------------------------------------------------------------------------------------------
Functions: vbl_request, ikbd_req, write_ikbd, read_from_ikbd,
clear_ikbd, is_ikbd_waiting,ini_mouse, update_mouse, ikbd_mouse_moved, install_vectors, 
remove_vectors, install_vector.
---------------------------------------------------------------------------------------------------
Issues/Problems:  None
---------------------------------------------------------------------------------------------------
Authors: - CLENCY TABE AND GLENN YEAP
---------------------------------------------------------------------------------------------------

*/

#include "include\ISR.H"

typedef UINT8 SCANCODE;

int GAME_TIMER = 0;
int MUIC_TIMER = 0;
int RENDER_REQUEST = 0;
int CHERRY_TIMER = 0;
int PACMAN_SUPER_TIMER = 0;

Vector VBL_VECTOR;
Vector IKBD_VECTOR;

volatile UINT8 *const ikbd_control = 0xFFFC00;
volatile const UINT8 *const ikbd_status = 0xFFFC00;
volatile const SCANCODE *const ikbd_reader = 0xFFFC02;

volatile UINT8 *const isrb_mfp_register = 0xFFFFA11;

/* keyboard values */
UINT8 IKBD_BUFFER[IKBD_BUFFER_SIZE];
UINT16 BUFF_HEAD = 0;
UINT16 BUFF_TAIL = 0;
UINT8 repeated_key = 0;

/* mouse values */
int mouse_state = FALSE;
UINT8 mouse_button;
UINT8 mouse_delta_x;
UINT8 mouse_delta_y;
int key_repeat = FALSE;
int mouse_moved = FALSE;

/* mouse globals */
int MOUSE_X = 0;
int MOUSE_Y = 0;
int MOUSE_LEFT_CLICK = FALSE;

int prev_mouse_x = 0;
int prev_mouse_y = 0;

/*
    array of ascii values for the keyboard
    to convert from scancode to ascii
*/
const UINT8 asciiLookup[115] = {
    0x00, /* 00 | DNE */
    0x1B, /* 01 | ESC */
    0x31, /* 02 | 1 */
    0x32, /* 03 | 2 */
    0x33, /* 04 | 3 */
    0x34, /* 05 | 4 */
    0x35, /* 06 | 5 */
    0x36, /* 07 | 6 */
    0x37, /* 08 | 7 */
    0x38, /* 09 | 8 */
    0x39, /* 0A | 9 */
    0x30, /* 0B | 0 */
    0x2D, /* 0C | - */
    0x3D, /* 0D | = */
    0x08, /* 0E | BKSP */
    0x09, /* 0F | TAB */
    0x71, /* 10 | Q */
    0x77, /* 11 | W */
    0x65, /* 12 | E */
    0x72, /* 13 | R */
    0x74, /* 14 | T */
    0x79, /* 15 | Y */
    0x75, /* 16 | U */
    0x69, /* 17 | I */
    0x6F, /* 18 | O */
    0x70, /* 19 | P */
    0x5B, /* 1A | [ */
    0x5D, /* 1B | ] */
    0x0D, /* 1C | RTRN */
    0x00, /* 1D | CTRL */
    0x61, /* 1E | A */
    0x73, /* 1F | S */
    0x64, /* 20 | D */
    0x66, /* 21 | F */
    0x67, /* 22 | G */
    0x68, /* 23 | H */
    0x6A, /* 24 | J */
    0x6B, /* 25 | K */
    0x6C, /* 26 | L */
    0x3B, /* 27 | ; */
    0x27, /* 28 | ' */
    0x60, /* 29 | EURO ' */
    0x00, /* 2A | LSHFT */
    0x5C, /* 2B | \ */
    0x7A, /* 2C | Z */
    0x78, /* 2D | X */
    0x63, /* 2E | C */
    0x76, /* 2F | V */
    0x62, /* 30 | B */
    0x6E, /* 31 | N */
    0x6D, /* 32 | M */
    0x2C, /* 33 | , */
    0x2E, /* 34 | . */
    0x2F, /* 35 | / */
    0x00, /* 36 | RSHFT */
    0x00, /* 37 | DNE */
    0x00, /* 38 | ALT */
    0x20, /* 39 | SPC */
    0x00, /* 3A | CAPS */
    0x00, /* 3B | F1 */
    0x00, /* 3C | F2 */
    0x00, /* 3D | F3 */
    0x00, /* 3E | F4 */
    0x00, /* 3F | F5 */
    0x00, /* 40 | F6 */
    0x00, /* 41 | F7 */
    0x00, /* 42 | F8 */
    0x00, /* 43 | F9 */
    0x00, /* 44 | F10 */
    0x00, /* 45 | DNE */
    0x00, /* 46 | DNE */
    0x00, /* 47 | HOME */
    0x18, /* 48 | UP ARW */
    0x00, /* 49 | DNE */
    0x2D, /* 4A | NUM - */
    0x1B, /* 4B | LFT ARW */
    0x00, /* 4C | DNE */
    0x1A, /* 4D | RT ARW */
    0x2B, /* 4E | NUM + */
    0x00, /* 4F | DNE */
    0x19, /* 50 | DN ARW */
    0x00, /* 51 | DNE */
    0x00, /* 52 | INSRT */
    0x7F, /* 53 | DEL */
    0x00, /* 54 | DNE */
    0x00, /* 55 | DNE */
    0x00, /* 56 | DNE */
    0x00, /* 57 | DNE */
    0x00, /* 58 | DNE */
    0x00, /* 59 | DNE */
    0x00, /* 5A | DNE */
    0x00, /* 5B | DNE */
    0x00, /* 5C | DNE */
    0x00, /* 5D | DNE */
    0x00, /* 5E | DNE */
    0x00, /* 5F | DNE */
    0x00, /* 60 | DNE */
    0x00, /* 61 | UNDO */
    0x00, /* 62 | HELP */
    0x28, /* 63 | NUM ( */
    0x29, /* 64 | NUM ) */
    0x2F, /* 65 | NUM / */
    0x2A, /* 66 | NUM * */
    0x37, /* 67 | NUM 7 */
    0x38, /* 68 | NUM 8 */
    0x39, /* 69 | NUM 9 */
    0x34, /* 6A | NUM 4 */
    0x35, /* 6B | NUM 5 */
    0x36, /* 6C | NUM 6 */
    0x31, /* 6D | NUM 1 */
    0x32, /* 6E | NUM 2 */
    0x33, /* 6F | NUM 3 */
    0x30, /* 70 | NUM 0 */
    0x2E, /* 71 | NUM . */
    0x0D  /* 72 | NUM ENTR */

};

/*
    *  vbl_request
    *
    *  This function is called by the VBL interrupt handler.
    *  It is used to set flags that are used to trigger
    *  rendering and game logic updates.
*/
void vbl_request()
{
    RENDER_REQUEST = TRUE;
    GAME_TIMER++;
    MUIC_TIMER++;
    CHERRY_TIMER++;
    PACMAN_SUPER_TIMER++;
}

/*
    *  ikbd_req
    *
    *  This function is called by the IKBD interrupt handler.
    *  It is used to read the IKBD and process the data.
*/
void ikbd_req()
{
    UINT8 scancode;

    *ikbd_control = 0x16;

    if (*ikbd_status & 0x01)
    {
        scancode = *ikbd_reader;

        if (mouse_state == MOUSE_STATE_FIRST_PACKET)
        {
            if (scancode >= MOUSE_MOVE_CODE)
            {
                mouse_button = scancode;
                mouse_state = MOUSE_STATE_DELTA_X;

                mouse_moved = scancode == MOUSE_MOVE_CODE;
            }
            else if ((scancode & IDLE) == 0x00) /* check if it's a make code */
            {
                write_ikbd(scancode);
                key_repeat = TRUE;
            }
            else if ((scancode & IDLE) == IDLE) /* check if it's a break code */
            {
                key_repeat = FALSE;
            }
        }
        else if (mouse_state == MOUSE_STATE_DELTA_X)
        {
            mouse_state = MOUSE_STATE_DELTA_Y;
            mouse_delta_x = scancode;
        }
        else if (mouse_state == MOUSE_STATE_DELTA_Y)
        {
            mouse_state = MOUSE_STATE_FIRST_PACKET;
            mouse_delta_y = scancode;
        }

        *isrb_mfp_register &= MFB_BIT_6_MASK_OFF; /* disable IKBD interrupt */
    }

    *ikbd_control = 0x96;
}

/*
    *  write_ikbd
    *
    *  This function is used to write a scancode to the IKBD buffer.
*/
void write_ikbd(UINT8 scancode)
{
    if (BUFF_TAIL == IKBD_BUFFER_SIZE - 1)
        BUFF_TAIL = 0;

    IKBD_BUFFER[BUFF_TAIL] = scancode;
    BUFF_TAIL++;
}

/*
    *  is_ikbd_waiting
    *
    *  This function is used to check if there is data in the IKBD buffer.
    *  It reads and returns the first scancode from buffer and converts it to ascii.
*/
UINT32 read_from_ikbd()
{
    UINT32 scancode;
    UINT32 old_ssp = Super(0);

    if (BUFF_HEAD == IKBD_BUFFER_SIZE - 1)
        BUFF_HEAD = 0;

    *isrb_mfp_register &= MFB_BIT_6_MASK_OFF; /* disable IKBD interrupt */

    scancode = IKBD_BUFFER[BUFF_HEAD];
    scancode = scancode << 16;
    scancode = scancode + asciiLookup[IKBD_BUFFER[BUFF_HEAD]];

    BUFF_HEAD++;

    *isrb_mfp_register |= MFB_BIT_6_MASK_ON; /* enable IKBD interrupt */

    Super(old_ssp);
    return scancode;
}

/*
    *  clear_ikbd
    *
    *  This function is used to clear the IKBD buffer.
*/
void clear_ikbd()
{
    while (is_ikbd_waiting())
    {
        BUFF_HEAD++;
    }

    IKBD_BUFFER[BUFF_TAIL] = 0x00;
}

/*
    *  is_ikbd_waiting
    *
    *  This function is used to check if there is data in the IKBD buffer.
*/
int is_ikbd_waiting()
{
    return BUFF_TAIL != BUFF_HEAD;
}

/*
    *  is_key_pressed
    *
    *  This function is used to check if a key is pressed.
*/
void ini_mouse(UINT16 *base)
{
    MOUSE_X = 320;
    MOUSE_Y = 200;
    prev_mouse_x = MOUSE_X;
    prev_mouse_y = MOUSE_Y;
    save_mouse_bg(base, MOUSE_X, MOUSE_Y);
    render_mouse(base, MOUSE_X, MOUSE_Y);
}

/*
    *  is_key_pressed
    *
    *  This function is used to check if a key is pressed.
*/
void update_mouse(UINT16 *base)
{
    MOUSE_X += (int)((char)mouse_delta_x);
    MOUSE_Y += (int)((char)mouse_delta_y);

    if (MOUSE_X < 0)
        MOUSE_X = 0;
    else if (MOUSE_X > 624)
        MOUSE_X = 624;

    if (MOUSE_Y < 0)
        MOUSE_Y = 0;
    else if (MOUSE_Y > 384)
        MOUSE_Y = 384;

    MOUSE_LEFT_CLICK = mouse_button == MOUSE_LEFT_BUTTON_CODE;

    mouse_delta_x = 0;
    mouse_delta_y = 0;

    clear_region_16_2(base, prev_mouse_x, prev_mouse_y, MOUSE_SIZE);
    restore_mouse_bg(base, prev_mouse_x, prev_mouse_y);
    save_mouse_bg(base, MOUSE_X, MOUSE_Y);
    render_mouse(base, MOUSE_X, MOUSE_Y);

    prev_mouse_x = MOUSE_X;
    prev_mouse_y = MOUSE_Y;
}

/*
    *  is_key_pressed
    *
    *  This function is used to check if a key is pressed.
*/
int ikbd_mouse_moved()
{
    return mouse_moved;
}

/*
    *  is_key_pressed
    *
    *  This function is used to check if a key is pressed.
*/
void install_vectors()
{
    VBL_VECTOR = install_vector(VBL_ISR, vbl_isr);
    IKBD_VECTOR = install_vector(IKBD_ISR, ikbd_isr);
}

/*
    *  install_vector
    *
    *  This function is used to install a new interrupt vector.
*/
Vector install_vector(int vector, Vector new_vector)
{
    Vector *vector_ptr = (Vector *)((UINT32)vector << 2);
    Vector old_vector;

    UINT32 old_ssp = Super(0);

    old_vector = *vector_ptr;
    *vector_ptr = new_vector;

    Super(old_ssp);
    return old_vector;
}

/*
    *  remove_vectors
    *
    *  This function is used to remove the interrupt vectors.
*/
void remove_vectors()
{
    install_vector(VBL_ISR, VBL_VECTOR);
    install_vector(IKBD_ISR, IKBD_VECTOR);
}
