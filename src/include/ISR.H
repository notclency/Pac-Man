#ifndef ISR_H
#define ISR_H

#include "TYPES.H"
#include "VBL.H"
#include "IKBD.H"
#include "MUSIC.H"
#include "RENDERER.H"
#include "CONSTS.H"

/* ISR */
#define VBL_ISR 28
#define IKBD_ISR 70
#define IDLE 0x80

#define IKBD_BUFFER_SIZE 256

#define MOUSE_STATE_FIRST_PACKET 0
#define MOUSE_STATE_DELTA_X 1
#define MOUSE_STATE_DELTA_Y 2

#define MFB_BIT_6_MASK_ON 0x40
#define MFB_BIT_6_MASK_OFF 0xbf

#define MOUSE_MOVE_CODE 0xF8
#define MOUSE_LEFT_BUTTON_CODE 0xFA

typedef void (*Vector) ();

/*
    Timers
*/
extern int GAME_TIMER;
extern int CHERRY_TIMER;
extern int PACMAN_SUPER_TIMER;
extern int MUIC_TIMER;

/*
    RENDER REQUESTS
*/
extern int RENDER_REQUEST;

/*
 * Mouse globals
 */
extern int MOUSE_X;
extern int MOUSE_Y;
extern int MOUSE_LEFT_CLICK;

extern UINT8 mouse_button;
extern UINT8 mouse_delta_y;
extern UINT8 mouse_delta_x;
extern int prev_mouse_x;
extern int prev_mouse_y;
extern int key_repeat;
extern int mouse_moved;

/* keyboard values */
extern UINT8 repeated_key;
extern UINT8 IKBD_BUFFER[IKBD_BUFFER_SIZE];
extern UINT16 BUFF_HEAD;
extern UINT16 BUFF_TAIL;

/* vectors */
extern Vector vbl_vector;
extern Vector ikbd_vector;

/*
    parameters:
        void

    description:
        proccesses the VBL request. 
        It updates the timers and the render request

    return:
        void
*/
void vbl_request();

/*
    parameters:
        void

    description:
        processes the IKBD request
*/
void ikbd_req();

/*
    parameters:
        scancode: scancode to write to the IKBD buffer

    description:
        writes a scancode to the IKBD buffer

    return:
        void
*/
void write_ikbd(UINT8 scancode);

/*
    parameters:
        void

    description:
        reads a scancode from the IKBD buffer

    return:
        scancode
*/
UINT32 read_from_ikbd();

/*
    parameters:
        void

    description:
        clears the IKBD buffer

    return:
        void
*/
void clear_ikbd();

/*
    parameters:
        void

    description:
        checks if the IKBD buffer is empty

    return:
        TRUE if the IKBD buffer is empty
        FALSE otherwise
*/
int is_ikbd_waiting();

/*
    parameters:
        void

    description:
        initializes the mouse

    return:
        void
*/
void ini_mouse(UINT16 *base);

/*
    parameters:
        void

    description:
        updates the mouse position & parameters (left click)

    return:
        void
*/
void update_mouse(UINT16 *base);

/*
    parameters:
        void

    description:
        checks if the mouse has moved

    return:
        TRUE if the mouse has moved
        FALSE otherwise
*/
int ikbd_mouse_moved();

/*
    parameters:
        void

    description:
        installs the VBL & IKBD vectors

    return:
        void
*/
void install_vectors();

/*
    parameters:
        void

    description:
        removes the VBL & IKBD vectors

    return:
        void
*/
void remove_vectors();

/*
    parameters:
        vector: vector to install
        new_vector: new vector

    description:
        installs a new vector (passed as parameter)

    return:
        old vector
*/
Vector install_vector(int vector, Vector new_vector);

#endif