#include "EVENTS.H"

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

void on_ghost_move(Model *model, int player)
{

    /* chase option */

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        if (model->ghosts[i].is_dead == FALSE)
        {
            move_ghost(&model->ghosts[i], &model->pacman[player]);
        }
    }
}

void on_snack_eat(Model *model, int player)
{
    int pacman_x = get_pacman_x(&model->pacman[player]);
    int pacman_y = get_pacman_y(&model->pacman[player]);

    model->pacman[player].score += 50;
    model->snacks[MAZE_ARRAY_WIDTH * pacman_y + pacman_x].eaten = TRUE;
    update_scorebox(model, player);
}

void on_cherry_eat(Model *model, int player)
{
    model->pacman[player].score += 100;
    /* eat = TRUE */
    update_scorebox(model, player);
}

void on_glow_ball_eat(Model *model, int player)
{
    int j = 0;

    model->pacman[player].score += 200;
    model->pacman[player].mode = SUPER;
    update_scorebox(model, player);
    /*
    for (j = 0; j < 3; j++)
    {
        model->ghosts[j].mode = SCATTER;
    }
    */
}

void on_ghost_eat(Model *model, int ghost_i, int player)
{
    int pacman_x = get_pacman_x(&model->pacman[player]);
    int pacman_y = get_pacman_y(&model->pacman[player]);
    int i = 0;

    if (model->pacman[player].mode == SUPER)
    {
        model->pacman[player].score += 200;
        model->ghosts[ghost_i].is_dead = TRUE;
        update_scorebox(model, player);

        /* initialize single ghost function */
        reset_ghost(&model->ghosts[i]);
        return;
    }
    else
    {
        /* initialize pacman & reduce lives */
        model->pacman[player].lives -= 1;

        if (model->pacman[player].lives == 0)
        {
            on_game_over(model);
        }

        reset_pacman(model, player);
        return;
    }
}

void on_game_start(Model *model, int player_count, int player)
{
    ini_game_session(model, player_count, player);
}

void on_game_over(Model *model)
{
    close_game_session(model);
}

void on_game_win(Model *model, int player_count)
{
    won_game_session(model);
}
