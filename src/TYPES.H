#ifndef TYPES_H
#define TYPES_H

typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;

typedef enum {
    black = 0xff,
    white = 0x00
} colors;

typedef enum {
    left, right, up, down
} direction;

typedef enum {
    dead, alive
} state;

typedef enum mode {
    normal, super, scared
} mode;

#endif
