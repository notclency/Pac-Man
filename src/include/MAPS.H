#ifndef PACMAN_MAPS_H
#define PACMAN_MAPS_H

#define MAZE_ARRAY_HEIGHT 17
#define MAZE_ARRAY_WIDTH 30

/*
    maze array contaiing the maze's 
    and accessable paths  

    0 = path
    1 = wall
*/
extern int maze_array[17][30];

/*
    snack array containing snack locations
    0 = snack
    1 = no snack
*/
extern int snack_array[17][30];

#endif
