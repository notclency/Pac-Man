#ifndef SPRITES_H
#define SPRITES_H

#include "TYPES.H"

#define CHARACTER_SIZE 16
#define MOUSE_SIZE 16

/* mouse sprite */
extern UINT16 mouse_bg_1[16];
extern UINT16 mouse_bg_2[16];

extern UINT16 mouse_ptr[16];


/* pacman sprites */
extern const UINT16 pacman_closed[16];

extern const UINT16 pacman_right[16];
extern const UINT16 pacman_right_open[16];

extern const UINT16 pacman_left[16];
extern const UINT16 pacman_left_open[16];

extern const UINT16 pacman_up[16];
extern const UINT16 pacman_up_open[16];

extern const UINT16 pacman_down[16];
extern const UINT16 pacman_down_open[16];

/* snack, glow ball and cherry sprite */
extern const UINT16 snack_sprite[16];
extern const UINT16 cherry_sprite[16];
extern const UINT16 glow_ball_sprite[16];

/* ghost sprites */
extern const UINT16 ghost_sprite[16];
extern const UINT16 ghost_scatter_sprite[16];

#endif