/*

---------------------------------------------------------------------------------------------------
File Name: EVENTS.C
---------------------------------------------------------------------------------------------------
Purpose: This file contains the functions that are called when certain events occur. All of these
functions are made to allow the character's events to happen. When a event occurs, all these functions
are called. For example when pacman moves, the on_pacman_move function is called to determine what
event action should happen.
---------------------------------------------------------------------------------------------------
Functions: on_pacman_move, on_ghost_move, on_snack_eat, on_cherry_eat, on_glow_ball_eat, on_ghost_eat,
key_input, get_input, mouse_input, on_game_start, on_game_over, on_game_win.
---------------------------------------------------------------------------------------------------
Issues/Problems:  None
---------------------------------------------------------------------------------------------------
Authors: - CLENCY TABE AND GLENN YEAP
---------------------------------------------------------------------------------------------------

*/
#include "include/EVENTS.H"

/*
    parameters:
        model: model struct
        key: key pressed
        player: player number

    description:
        called when key is pressed to move pacman (ie change direction)

    return:
*/
void on_pacman_move(Model *model, UINT32 key, int player)
{
    switch (key)
    {
    case UP_KEY:
        move_pacman(model, UP, player);
        break;
    case DOWN_KEY:
        move_pacman(model, DOWN, player);
        break;
    case LEFT_KEY:
        move_pacman(model, LEFT, player);
        break;
    case RIGHT_KEY:
        move_pacman(model, RIGHT, player);
        break;
    }
}

/*
    parameters:
        model: model struct
        player: player number

    description:
        called when ghosts moves

    return:
*/
void on_ghost_move(Model *model, int player)
{
    int pacman_x = model->pacman[player].x;
    int pacman_y = model->pacman[player].y;

    int ghost_x;
    int ghost_y;

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        if (model->ghosts[i].is_dead == FALSE)
        {
            if (model->pacman[player].mode == NORMAL)
            {
                ghost_x = model->ghosts[i].x;
                ghost_y = model->ghosts[i].y;

                if (abs(pacman_x - ghost_x) < 10 && abs(pacman_y - ghost_y) < 10) {
                    model->ghosts[i].mode = CHASE;
                } else {
                    model->ghosts[i].mode = ROAM;
                }
            }
            else if (model->pacman[player].mode == SUPER)
            {
                model->ghosts[i].mode = SCATTER;
            }

            move_ghost(&model->ghosts[i], &model->pacman[player]);
        }
    }
}

/*
    parameters:
        model: model struct
        player: player number

    description:
        called when snack is eaten

    return:
*/
void on_snack_eat(Model *model, int player)
{
    pacman *pacman = &model->pacman[player];

    int pacman_x = model->pacman[player].x;
    int pacman_y = model->pacman[player].y;

    pacman->score += 50;
    pacman->snacks_eaten++;
    model->snacks[MAZE_ARRAY_WIDTH * pacman_y + pacman_x].eaten = TRUE;
    if (pacman->snacks_eaten == 196)
    {
        model->game_won = 1;
    }
}

/*
    parameters:
        model: model struct
        player: player number

    description:
        called when cherry is eaten

    return:
*/
void on_cherry_eat(Model *model, int player)
{
    model->pacman[player].score += 100;
    model->cherries[0].eaten = TRUE;
}

/*
    parameters:
        model: model struct
        player: player number

    description:
        called when glow ball is eaten

    return:
*/
void on_glow_ball_eat(Model *model, int player)
{
    int j;

    model->pacman[player].score += 200;
    model->pacman[player].mode = SUPER;

    for (j = 0; j < 3; j++)
    {
        model->ghosts[j].mode = SCATTER;
    }
}

/*
    parameters:
        model: model struct
        ghost_i: ghost index
        player: player number

    description:
        called when ghost is eaten

    return:
*/
void on_ghost_eat(Model *model, int ghost_i, int player)
{
    pacman *pacman = &model->pacman[player];
    ghost *ghost = &model->ghosts[ghost_i];

    int i = 0;

    if (pacman->mode == SUPER)
    {
        pacman->score += 200;
        ghost->is_dead = TRUE;

        /* initialize single ghost function */
        reset_ghost(ghost);
        return;
    }
    else
    {
        /* reset pacman */
        pacman->lives--;
        pacman->is_dead = TRUE;
        is_dead(model, player);
        return;
    }
}

/*
    parameters:
        None
    
    description:
        checks if key is pressed

    return:
        1 if key is pressed, 0 otherwise
*/
int key_input()
{
    return is_ikbd_waiting();
}

/*
    parameters:
        None
    
    description:
        gets key pressed

    return:
        key pressed
*/
UINT32 get_input()
{
    return read_from_ikbd();
}

/*
    parameters:
        None
    
    description:
        checks if mouse is moved

    return:
        1 if mouse is moved, 0 otherwise
*/
int mouse_input()
{
    return ikbd_mouse_moved();
}

void on_game_start(Model *model, int player_count, int player)
{
    ini_game_session(model, player_count, player);
}
