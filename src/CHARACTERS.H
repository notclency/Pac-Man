#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "types.h"

typedef struct {
    unsigned int x, y;
    int delta_x, delta_y;
    int lives;
    int score;
    int state;
} pacman;

struct ghost {
    int x;
    int y;
    int direction;
    int speed;
    int state;
};

struct snack_Pallete {
    int x;
    int y;
    int state;
    int speed;
};

struct glowing_ball{ 
    int x;
    int y;
    int state;
    int speed;
};

struct cherry {
    int x;
    int y;
    int state;
    int speed;
};

#endif