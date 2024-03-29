#ifndef PACMAN_EVENTS_H
#define PACMAN_EVENTS_H

#include "TYPES.H"
#include "MODEL.H"
#include "CONSTS.H"
#include "ISR.H"

/*
    parameters:
        model: model struct
        key: key pressed
        player: player number

    description:
        called when key is pressed to move pacman (ie change direction)

    return:
*/
void on_pacman_move(Model *model, UINT32 key, int player);

/*
    parameters:
        model: model struct
        player: player number

    description:
        called when ghosts moves

    return:
*/
void on_ghost_move(Model *model, int player);

/*
    parameters:
        model: model struct
        player: player number

    description:
        called when snack is eaten

    return:
*/
void on_snack_eat(Model *model, int player);

/*
    parameters:
        model: model struct
        player: player number

    description:
        called when cherry is eaten

    return:
*/
void on_cherry_eat(Model *model, int player);

/*
    parameters:
        model: model struct
        player: player number

    description:
        called when glow ball is eaten

    return:
*/
void on_glow_ball_eat(Model *model, int player);

/*
    parameters:
        model: model struct
        ghost_i: index of ghost
        player: player number

    description:
        called when ghost is eaten

    return:
*/
void on_ghost_eat(Model *model, int ghost_i, int player);

/*
    parameters:
        model: model struct
        player: player number

    description:
        called when pacman dies

    return:
*/
void on_game_over(Model *model);

/*
    parameters:
        model: model struct
        player_count: number of players

    description:
        called when game session is won

    return:
*/
void on_game_win(Model *model, int player_count);

/*
    parameters:
        model: model struct
        player_count: number of players
        player: player number

    description:
        called when game session is started

    return:
*/
void on_game_start(Model *model, int player_count, int player);

/*
    parameters:
        None.
    
    description:
        checks key input

    return:
        boolean value corresponding if key is pressed
*/
int key_input();

/*
    parameters:
        None.
    
    description:
        checks mouse input

    return:
        boolean value corresponding if mouse is pressed
*/
int mouse_input();

/*
    parameters:
        None.
    
    description:
        checks joystick input

    return:
        boolean value corresponding if joystick is pressed
*/
UINT32 get_input();

#endif
