#ifndef CONSTS_H
#define CONSTS_H

#include "TYPES.H"

/* PLAYER 1 & 2 */
#define PLAYER_1 0
#define PLAYER_2 1

/* move speeds */
#define PACMAN_MOVE_SPEED 1
#define GHOST_MOVE_SPEED 1
#define GHOST_SCARED_SPEED 8

/* event durations */
#define CHERRY_POP_TIME 20
#define CHERRY_COLLAPSE_TIME 40
#define PACMAN_SUPER_TIME 15

/* custom keyboard keys */
#define ESC_KEY 0x0001001B
#define LEFT_KEY 0x004B001B
#define RIGHT_KEY 0x004D001A
#define SPACE_KEY 0x00390020
#define UP_KEY 0x00480018
#define DOWN_KEY 0x00500019
#define ENTER_KEY 0x001C000D

/* atari screen */
#define SCREEN_HEIGHT 640
#define SCREEN_WIDTH 400

/* splash and map size */
#define SCREEN_BMP 8000
#define MAP_BMP 4080

/* PAD ITEMS CONSTS */
#define ALIGN_ITEM_X 6
#define ALIGN_ITEM_Y 5

/* PACMAN SPAWN X AND Y */
#define PACMAN_SPAWN_X 15
#define PACMAN_SPAWN_Y 13

#define PACMAN_LIVES 3

#define GHOST_SPAWN_X 19
#define GHOST_SPAWN_Y 6

/* TRUE OR FALSE */
#define TRUE 1
#define FALSE 0

#endif
