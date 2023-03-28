/*
Purpose: This fucntion is made to depict the ability of the all character move,eat,abilities and etc.
This function is used to decide the character's events and the events that take place in the game.

It calls the on_pacman_move, on_ghost_move,
on_snack_eat, on_pacman_death, on_ghost_death, 
on_pacman_super, on_pacman_normal, on_ghost_scatter, 
on_ghost_roam, on_game_over, on_game_win functions.

The events that take place in the game are handled in this function.
*/

#include "EVENTS.H"

/*
Input: Model *model, UINT32 key, int player
Purpose: This function purpose is to move the pacman in the direction of the key pressed/value.
It calls the move_pacman function to move the pacman in the direction.

LEFT_KEY 0x004b0000
RIGHT_KEY 0x004d0000
UP_KEY 0x00480000
DOWN_KEY 0x00500000
*/

void on_pacman_move(Model *model, UINT32 key, int player)
{
    switch (key)
    {
    case UP_KEY:
        move_pacman(model, UP, player); // move pacman up
        break;
    case DOWN_KEY:
        move_pacman(model, DOWN, player); // move pacman down
        break;
    case LEFT_KEY:
        move_pacman(model, LEFT, player); // move pacman left
        break;
    case RIGHT_KEY:
        move_pacman(model, RIGHT, player); // move pacman right
        break;
    }
}

/*
Input: Model *model, int player
Purpose: This function purpose is to move the ghost in the direction of the pacman. 
This function also calls the move_ghost function to move the ghost in the direction 
and changes the modes of the ghosts depending on the mode of the pacman.

*/


void on_ghost_move(Model *model, int player)
{

    /* chase option */
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        if (model->ghosts[i].is_dead == FALSE) // if ghost is not dead
        {
            if (model->pacman[player].mode == NORMAL) // if pacman is in normal mode
            {
                model->ghosts[i].mode = ROAM; // set ghost mode to roam
            }
            else if (model->pacman[player].mode == SUPER) // if pacman is in super mode
            {
                model->ghosts[i].mode = SCATTER; // set ghost mode to scatter
            }

            move_ghost(&model->ghosts[i], &model->pacman[player]); // move ghost
        }
    }
}
/*

Inputs: Model *model, int player
Purpose: This function purpose is to check if the pacman has eaten a snack and
adds points if the model has or not. It does the by checking the pacman x and y
to the snack x and y. If they are the same then the snack is eaten and the score
is added.

*/


void on_snack_eat(Model *model, int player)
{
    int pacman_x = get_pacman_x(&model->pacman[player]); // get pacman x
    int pacman_y = get_pacman_y(&model->pacman[player]); // get pacman y

    model->pacman[player].score += 50; // add score
    model->snacks[MAZE_ARRAY_WIDTH * pacman_y + pacman_x].eaten = TRUE; // set snack eaten to true

}

/*

Inputs: Model *model, int player
Purpose: This function purpose is to check if the pacman has eaten a cherry and
this done by getting the pacman x and y and checking if the cherry x and y are 
the same. If they are the same then the cherry is eaten and the score is added.

*/

void on_cherry_eat(Model *model, int player)
{
    int pacman_x = get_pacman_x(&model->pacman[player]); // get pacman x
    int pacman_y = get_pacman_y(&model->pacman[player]); // get pacman y

    model->pacman[player].score += 100; // add score
    model->cherry[MAZE_ARRAY_WIDTH * pacman_y + pacman_x].eaten = TRUE; // set cherry eaten to true
}

/*

Inputs: Model *model, int player
Purpose: This function purpose is to check if the pacman has eaten a glow ball and if 
pacman has eaten a glow ball it will set the pacman mode to SUPER and also set the ghosts 
modes to scatter mode and the score would be added for eating glowing ball. 

*/
void on_glow_ball_eat(Model *model, int player)
{
    int j = 0;

    model->pacman[player].score += 200; // add score
    model->pacman[player].mode = SUPER; // set pacman mode to super

    for (j = 0; j < 3; j++)
    {
        model->ghosts[j].mode = SCATTER; // set ghost mode to scatter
    }
}
/*

Inputs: Model *model, int player
Purpose: This function purpose is to check if the pacman has eaten a ghost and depending on the mode
it will make pacman die or alive. If the pacman is in super mode then the ghost will die and the score 
will be added. If the pacman is in normal mode then the pacman will die and the lives will be reduced.

*/
void on_ghost_eat(Model *model, int ghost_i, int player)
{
    int pacman_x = get_pacman_x(&model->pacman[player]); // get pacman x
    int pacman_y = get_pacman_y(&model->pacman[player]); // get pacman y
    int i = 0;

    if (model->pacman[player].mode == SUPER) // if pacman is in super mode
    {
        model->pacman[player].score += 200; // add score
        model->ghosts[ghost_i].is_dead = TRUE; // set ghost to dead

        /* initialize single ghost function */
        reset_ghost(&model->ghosts[ghost_i]); //   reset ghost to home base
        return;
    }
    else
    {
        /* reset pacman */
        model->pacman[player].lives--; // reduce lives
        model->pacman[player].is_dead = TRUE; // set pacman to dead
        is_dead(model, player); 
        return;
    }
}
/*

Inputs: Model *model, int player
Purpose: This function purpose is to know what the game mode is and if the game mode is one player
or two player. If the game mode is one player then the game sessuion will be initialized for one player
and if the game mode is two player then the game session will be initialized for two players.

*/

void on_game_start(Model *model, int player_count, int player)
{
    ini_game_session(model, player_count, player);
}

/*
Inputs: Model *model
Purpose: This function purpose is to close the game session.
*/
void on_game_over(Model *model)
{
    close_game_session(model);
}
/*

Inputs: Model *model, int player_count
Purpose: This function purpose is to know if the game has been won 

*/
void on_game_win(Model *model, int player_count)
{
    won_game_session(model);
}
