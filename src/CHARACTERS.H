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

struct snackPallete {
    int x;
    int y;
    int state;
};

struct fruit {
    int x;
    int y;
    int state;
};

#endif