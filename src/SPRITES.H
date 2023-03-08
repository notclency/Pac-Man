#ifndef SPRITES_H
#define SPRITES_H

#include "TYPES.H"

#define CHARACTER_SIZE 16

extern const UINT16 pacman_closed[16];

extern const UINT16 pacman_right[16];
extern const UINT16 pacman_right_open[16];

extern const UINT16 pacman_left[16];
extern const UINT16 pacman_left_open[16];

extern const UINT16 pacman_up[16];
extern const UINT16 pacman_up_open[16];

extern const UINT16 pacman_down[16];
extern const UINT16 pacman_down_open[16];

extern const UINT16 emp[16];

extern const UINT16 snack_sprite[16];
extern const UINT16 cherry_sprite[16];
extern const UINT16 glow_ball_sprite[16];

extern const UINT16 ghost_sprite[16];
extern const UINT16 ghost_scatter_sprite[16];


#define MAZE_ARRAY_HEIGHT 17
#define MAZE_ARRAY_WIDTH 30

extern int maze_array[17][30];
extern int snack_array[17][30];
extern int cherry_array[17][30];
extern int glow_ball_array[17][30];

#endif