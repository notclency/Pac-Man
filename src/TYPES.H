#ifndef TYPES_H
#define TYPES_H

/* #include <random> */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PLAYER_1 0
#define PLAYER_2 1

/* move speeds */
#define PACMAN_MOVE_SPEED 16
#define GHOST_MOVE_SPEED 16
#define GHOST_SCARED_SPEED 2

#define TRUE 1
#define FALSE 0

#define ESC_KEY 0x0001001b
#define LEFT_KEY 0x004b0000
#define RIGHT_KEY 0x004d0000
#define SPACE_KEY 0x00390020
#define UP_KEY 0x00480000
#define DOWN_KEY 0x00500000
#define ENTER_KEY 0x001C000D

#define SCREEN_HEIGHT 640
#define SCREEN_WIDTH 400

#define SCREEN_BMP 8000
#define MAP_BMP 4080

#define ALIGN_ITEM_X 6
#define ALIGN_ITEM_Y 5

#define SNACK_INI_X 7
#define SNACK_INI_Y 6

#define PACMAN_SPAWAN_X 28
#define PACMAN_SPAWAN_Y 18

typedef unsigned char UINT8;
typedef unsigned int UINT16;
typedef unsigned long UINT32;

typedef enum
{
    black = 0xff,
    white = 0x00
} colors;

typedef enum
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NONE
} direction;

typedef enum mode
{
    NORMAL,
    SUPER,
    SCATTER,
    ROAM,
    CHASE
} mode;

#endif
